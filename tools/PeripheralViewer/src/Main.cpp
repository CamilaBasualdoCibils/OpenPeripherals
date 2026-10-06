
#include "GLFW/glfw3.h"
#include "OpenPeripheral/EvDev/EvdevDevice.hpp"
#include "OpenPeripheral/EvDev/EvdevProvider.hpp"
#include "OpenPeripheral/OpenPeripherals.hpp"
#include "OpenPeripheral/Provider.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include <algorithm>
#include <boost/describe/enum_to_string.hpp>
#include <memory>
#include <stdexcept>
class PeripheralViewer {
public:
  PeripheralViewer() {
    if (glfwInit() != GLFW_TRUE)
      throw std::runtime_error("GLFW failed to initialize");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window_ =
        glfwCreateWindow(1200, 800, "OpenPeripherals Viewer", nullptr, nullptr);
    if (!window_)
      throw std::runtime_error("GLFW failed to create the window");
    glfwMakeContextCurrent(window_);
    glfwSwapInterval(1);
    ImGui::CreateContext();
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window_, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    providers_.push_back(std::make_unique<OpenPeripherals::EvdevProvider>());
    EnumerateDevices();
  }

  ~PeripheralViewer() {
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
    const ImGuiID dockspace_id = ImGui::GetID("PeripheralViewerDockspace");
    ImGui::DockSpaceOverViewport(dockspace_id);
    BuildDefaultDockLayout(dockspace_id);

    ImGui::Begin("Peripheral Tree###peripheral_tree");
    if (ImGui::Button("Refresh")) {
      EnumerateDevices();
    }
    ImGuiTreeNodeFlags root_flags =
        ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick |
        ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanAvailWidth;
    if (tree_selected_)
      root_flags |= ImGuiTreeNodeFlags_Selected;
    const bool root_open = ImGui::TreeNodeEx("Peripherals", root_flags);
    if (ImGui::IsItemClicked())
      tree_selected_ = true;
    if (root_open) {
      for (const auto &device : devices_) {
        const auto &info = device->GetInfo();
        ImGuiTreeNodeFlags device_flags = ImGuiTreeNodeFlags_OpenOnArrow |
                                          ImGuiTreeNodeFlags_OpenOnDoubleClick |
                                          ImGuiTreeNodeFlags_SpanAvailWidth;
        if (selected_device_ == device)
          device_flags |= ImGuiTreeNodeFlags_Selected;

        // Deliberately not a leaf node: child devices can be added here later.
        const bool open = ImGui::TreeNodeEx(
            static_cast<const void *>(device.get()), device_flags, "%s",
            info.name.empty() ? "Unnamed device" : info.name.c_str());
        if (ImGui::IsItemClicked())
          selected_device_ = device;
        if (open)
          ImGui::TreePop();
      }
      ImGui::TreePop();
    }
    ImGui::End();

    ImGui::Begin("Details###peripheral_details");
    if (selected_device_) {
      DrawDeviceDetails();
    }
    ImGui::End();
  }

  void BuildDefaultDockLayout(ImGuiID dockspace_id) {
    // Preserve any layout restored from imgui.ini or adjusted by the user.
    if (ImGui::DockBuilderGetNode(dockspace_id) != nullptr)
      return;

    ImGui::DockBuilderRemoveNode(dockspace_id);
    ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace);
    ImGui::DockBuilderSetNodeSize(dockspace_id,
                                  ImGui::GetMainViewport()->WorkSize);

    ImGuiID details_id = dockspace_id;
    const ImGuiID tree_id = ImGui::DockBuilderSplitNode(
        details_id, ImGuiDir_Left, 0.28F, nullptr, &details_id);
    ImGui::DockBuilderDockWindow("Peripheral Tree###peripheral_tree", tree_id);
    ImGui::DockBuilderDockWindow("Details###peripheral_details", details_id);
    ImGui::DockBuilderFinish(dockspace_id);
  }

  void EnumerateDevices() {
    OpenPeripherals::Instance ctx;
    for (const auto &provider : providers_) {
      ctx.RegisterProvider(provider);
    }
    devices_ = std::move(ctx.EnumerateDevices());
    if (selected_device_ && std::find(devices_.begin(), devices_.end(),
                                      selected_device_) == devices_.end()) {
      selected_device_.reset();
    }
  }
  void DrawEvdevDeviceDetails(
      const OpenPeripherals::Evdev::EvdevDevice &evdevDevice) {
    const auto &evdevInfo = evdevDevice.GetEvdevInfo();
    const auto &capabilities = evdevDevice.GetEvdevCapabilities();
    ImGui::Text("Evdev Bus: %s",
                boost::describe::enum_to_string(evdevInfo.bus, "Unknown"));
    if (ImGui::TreeNodeEx("EvDev", ImGuiTreeNodeFlags_DefaultOpen)) {
      for (const auto &[type, components] : capabilities.components) {
        const char *type_name =
            boost::describe::enum_to_string(type, "Unknown");
        ImGui::PushID(static_cast<int>(type));
        if (ImGui::TreeNodeEx(type_name, ImGuiTreeNodeFlags_DefaultOpen)) {
          for (const auto &component : components) {
            const std::string code_name = std::format(
                "type={}, code={} {}",
                boost::describe::enum_to_string(type, "Unknown"),
                boost::describe::enum_to_string(component.code, "Unknown"),
              component.hasAbsoluteInfo? "has absolute info":"");
            ImGui::TreeNodeEx(code_name.c_str(),
                              ImGuiTreeNodeFlags_Leaf |
                                  ImGuiTreeNodeFlags_NoTreePushOnOpen);
          }
          ImGui::TreePop();
        }
        ImGui::PopID();
      }
      ImGui::TreePop();
    }
  };
  void DrawDeviceDetails() {
    if (selected_device_) {
      const auto &info = selected_device_->GetInfo();
      ImGui::Text("Device Name: %s", info.name.c_str());
      ImGui::Text("Manufacturer: %s", info.manufacturer.c_str());
      ImGui::Text("Description: %s", info.description.c_str());

      ImGui::Separator();
      if (const auto evdevDevice =
              std::dynamic_pointer_cast<OpenPeripherals::Evdev::EvdevDevice>(
                  selected_device_)) {
        DrawEvdevDeviceDetails(*evdevDevice);
      }
    }
  }
  GLFWwindow *window_{};
  bool tree_selected_{};

  std::vector<std::shared_ptr<OpenPeripherals::IProvider>> providers_;
  std::vector<std::shared_ptr<OpenPeripherals::IPhysicalPeripheral>> devices_;
  std::shared_ptr<OpenPeripherals::IPhysicalPeripheral> selected_device_;
};

int main() {
  PeripheralViewer viewer;
  return viewer.Run();
}
