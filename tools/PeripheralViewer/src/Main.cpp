#include "GLFW/glfw3.h"
#include <OpenPeripherals/Core/OpenPeripherals.hpp>
#include <OpenPeripherals/Evdev/EvdevDiscovery.hpp>
#include "GraphLayout.hpp"
#include "GraphRenderer.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

#include <algorithm>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

class PeripheralViewerApp {
public:
  PeripheralViewerApp() {
    if (glfwInit() != GLFW_TRUE)
      throw std::runtime_error("GLFW failed to initialize");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window_ = glfwCreateWindow(1200, 800, "OpenPeripherals Viewer", nullptr,
                               nullptr);
    if (!window_)
      throw std::runtime_error("GLFW failed to create the window");
    glfwMakeContextCurrent(window_);
    glfwSwapInterval(1);
    ImGui::CreateContext();
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window_, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    providers_.push_back(std::make_shared<OpenPeripherals::EvdevDiscovery>());
    EnumeratePeripherals();
  }

  ~PeripheralViewerApp() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    if (window_)
      glfwDestroyWindow(window_);
    glfwTerminate();
  }

  int Run() {
    while (!glfwWindowShouldClose(window_)) {
      glfwPollEvents();
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();
      Draw();
      ImGui::Render();
      int width = 0, height = 0;
      glfwGetFramebufferSize(window_, &width, &height);
      glViewport(0, 0, width, height);
      glClearColor(0.045F, 0.05F, 0.065F, 1.0F);
      glClear(GL_COLOR_BUFFER_BIT);
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
      glfwSwapBuffers(window_);
    }
    return 0;
  }

private:
  void Draw() {
    const ImGuiID dockspaceId = ImGui::GetID("PeripheralViewerDockspace");
    ImGui::DockSpaceOverViewport(dockspaceId);
    BuildDefaultDockLayout(dockspaceId);

    DrawPeripheralList();
    DrawGraph();
    DrawDetails();
  }

  void DrawPeripheralList() {
    ImGui::Begin("Peripherals###peripheral_list");
    if (ImGui::Button("Refresh"))
      EnumeratePeripherals();
    ImGui::SameLine();
    ImGui::Text("%zu found", result_.peripherals.size());
    ImGui::Separator();

    for (const auto &peripheral : result_.peripherals) {
      const std::string label = peripheral.info.name.empty()
                                    ? "Unnamed peripheral"
                                    : peripheral.info.name;
      const bool selected = selectedPeripheral_ == peripheral.id;
      ImGui::PushID(peripheral.id.to_string().c_str());
      if (ImGui::Selectable(label.c_str(), selected))
        selectedPeripheral_ = peripheral.id;
      ImGui::PopID();
    }
    ImGui::End();
  }

  void DrawGraph() {
    ImGui::Begin("Connections###peripheral_graph");
    ImGui::TextUnformatted("This machine and its connected peripherals.");
    ImGui::SameLine();
    ImGui::TextDisabled("Arrows show connection direction.");

    ImVec2 canvasSize = ImGui::GetContentRegionAvail();
    canvasSize.x = std::max(canvasSize.x, 220.0F);
    canvasSize.y = std::max(canvasSize.y, 180.0F);
    ImGui::InvisibleButton("graph_canvas", canvasSize);
    const ImVec2 canvasMin = ImGui::GetItemRectMin();
    const ImVec2 canvasMax = ImGui::GetItemRectMax();
    ImDrawList *drawList = ImGui::GetWindowDrawList();
    const auto &graph = result_.graph.GetGraph();
    const auto &positions = layout_.Update(graph, ImGui::GetIO().DeltaTime);
    const auto interaction = renderer_.Draw(
        drawList, graph, positions, canvasMin, canvasMax, selectedPeripheral_,
        cameraOffset_, cameraZoom_);
    cameraOffset_.x += interaction.cameraPanDelta.x;
    cameraOffset_.y += interaction.cameraPanDelta.y;
    if (interaction.cameraZoomFactor != 1.0F) {
      const float oldZoom = cameraZoom_;
      cameraZoom_ = std::clamp(
          cameraZoom_ * interaction.cameraZoomFactor,
          renderer_.Config().minimumZoom, renderer_.Config().maximumZoom);
      const float zoomRatio = cameraZoom_ / oldZoom;
      cameraOffset_.x = interaction.cameraAnchor.x -
                        (interaction.cameraAnchor.x - cameraOffset_.x) * zoomRatio;
      cameraOffset_.y = interaction.cameraAnchor.y -
                        (interaction.cameraAnchor.y - cameraOffset_.y) * zoomRatio;
    }
    if (interaction.clickedNode)
      selectedPeripheral_ = interaction.clickedNode;
    if (interaction.draggedNode) {
      layout_.MoveNode(*interaction.draggedNode, interaction.dragPosition, true);
    }
    if (interaction.dragEnded && !renderer_.Config().pinAfterDrag)
      layout_.SetPinned(*interaction.dragEnded, false);
    if (boost::num_vertices(graph) == 0)
      drawList->AddText(ImVec2(canvasMin.x + 18.0F, canvasMin.y + 18.0F),
                        IM_COL32(190, 196, 208, 255), "No graph nodes");
    ImGui::End();
  }

  void DrawDetails() {
    ImGui::Begin("Details###peripheral_details");
    if (selectedPeripheral_) {
      const auto vertex = result_.graph.FindPeripheral(*selectedPeripheral_);
      if (vertex && result_.graph.GetGraph()[*vertex].type ==
                        OpenPeripherals::Graph::PeripheralNodeType::Machine) {
        const auto &machine = result_.graph.GetGraph()[*vertex];
        ImGui::TextUnformatted(machine.name.c_str());
        ImGui::Separator();
        ImGui::Text("ID: %s", machine.id.to_string().c_str());
        ImGui::TextWrapped("Local root for peripherals discovered on this machine.");
        ImGui::End();
        return;
      }
    }

    const auto selected = FindSelectedPeripheral();
    if (!selected) {
      ImGui::TextDisabled("Select a peripheral to see its description.");
      ImGui::End();
      return;
    }

    const auto &peripheral = *selected;
    ImGui::TextWrapped("%s", peripheral.info.name.empty()
                                 ? "Unnamed peripheral"
                                 : peripheral.info.name.c_str());
    ImGui::Separator();
    ImGui::Text("ID: %s", peripheral.id.to_string().c_str());
    ImGui::Text("Manufacturer: %s",
                peripheral.info.manufacturer.empty()
                    ? "Unknown"
                    : peripheral.info.manufacturer.c_str());
    ImGui::Text("Model: %s", peripheral.info.model.empty()
                                 ? "Unknown"
                                 : peripheral.info.model.c_str());
    ImGui::TextWrapped("Description: %s",
                       peripheral.info.description.empty()
                           ? "No description"
                           : peripheral.info.description.c_str());

    ImGui::Separator();
    ImGui::Text("Endpoints: %zu", peripheral.endpoints.size());
    for (const auto &endpoint : peripheral.endpoints) {
      ImGui::BulletText("%s: %s", endpoint.connectionType.c_str(),
                        endpoint.address.c_str());
    }
    ImGui::Text("States: %zu   Events: %zu", peripheral.states.size(),
                peripheral.events.size());
    ImGui::Text("Streams: %zu   Operations: %zu   Resources: %zu",
                peripheral.streams.size(), peripheral.operations.size(),
                peripheral.resources.size());

    if (!peripheral.identity.claims.empty()) {
      ImGui::Separator();
      ImGui::TextUnformatted("Identity claims");
      for (const auto &claim : peripheral.identity.claims)
        ImGui::BulletText("%u: %s", static_cast<unsigned int>(claim.type),
                          claim.value.c_str());
    }
    ImGui::End();
  }

  const OpenPeripherals::PhysicalPeripheral *FindSelectedPeripheral() const {
    if (!selectedPeripheral_)
      return nullptr;
    const auto found = std::find_if(
        result_.peripherals.begin(), result_.peripherals.end(),
        [this](const auto &peripheral) {
          return peripheral.id == *selectedPeripheral_;
        });
    return found == result_.peripherals.end() ? nullptr : &*found;
  }

  void BuildDefaultDockLayout(ImGuiID dockspaceId) {
    if (ImGui::DockBuilderGetNode(dockspaceId) != nullptr)
      return;

    ImGui::DockBuilderRemoveNode(dockspaceId);
    ImGui::DockBuilderAddNode(dockspaceId, ImGuiDockNodeFlags_DockSpace);
    ImGui::DockBuilderSetNodeSize(dockspaceId,
                                  ImGui::GetMainViewport()->WorkSize);

    ImGuiID centerId = dockspaceId;
    const ImGuiID listId = ImGui::DockBuilderSplitNode(
        centerId, ImGuiDir_Left, 0.24F, nullptr, &centerId);
    const ImGuiID detailsId = ImGui::DockBuilderSplitNode(
        centerId, ImGuiDir_Right, 0.28F, nullptr, &centerId);
    ImGui::DockBuilderDockWindow("Peripherals###peripheral_list", listId);
    ImGui::DockBuilderDockWindow("Connections###peripheral_graph", centerId);
    ImGui::DockBuilderDockWindow("Details###peripheral_details", detailsId);
    ImGui::DockBuilderFinish(dockspaceId);
  }

  void EnumeratePeripherals() {
    OpenPeripherals::Instance instance;
    for (const auto &provider : providers_)
      instance.RegisterDiscover(provider);
    result_ = instance.EnumeratePeripherals();
    layout_.Reset();

    if (selectedPeripheral_ &&
        !result_.graph.FindPeripheral(*selectedPeripheral_))
      selectedPeripheral_.reset();
  }

  GLFWwindow *window_{};
  std::vector<std::shared_ptr<OpenPeripherals::IDiscovery>> providers_;
  OpenPeripherals::EnumerationResult result_;
  std::optional<OpenPeripherals::PeripheralID> selectedPeripheral_;
  PeripheralViewer::SpringGraphLayout layout_;
  PeripheralViewer::PeripheralGraphRenderer renderer_;
  PeripheralViewer::GraphPoint cameraOffset_{};
  float cameraZoom_{1.0F};
};

int main() {
  PeripheralViewerApp viewer;
  return viewer.Run();
}
