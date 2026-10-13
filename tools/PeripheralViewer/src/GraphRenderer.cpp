#include "GraphRenderer.hpp"

#include <algorithm>
#include <cmath>
#include <limits>
#include <set>
#include <string>
#include <vector>

namespace PeripheralViewer {

GraphInteraction PeripheralGraphRenderer::Draw(
    ImDrawList *drawList, const Graph &graph, const Positions &positions,
    ImVec2 canvasMin, ImVec2 canvasMax,
    std::optional<OpenPeripherals::PeripheralID> selected,
    GraphPoint cameraOffset, float cameraZoom) {
  GraphInteraction interaction;
  drawList->AddRectFilled(canvasMin, canvasMax, config_.backgroundColor, 6.0F);
  const ImVec2 center((canvasMin.x + canvasMax.x) * 0.5F,
                      (canvasMin.y + canvasMax.y) * 0.5F);
  const ImVec2 mouse = ImGui::GetIO().MousePos;
  if (ImGui::IsItemHovered() && ImGui::GetIO().MouseWheel != 0.0F) {
    const float factor = std::pow(1.15F, ImGui::GetIO().MouseWheel);
    interaction.cameraZoomFactor = factor;
    interaction.cameraAnchor = {mouse.x - center.x, mouse.y - center.y};
  }
  if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Middle)) {
    panning_ = true;
    panLastMouse_ = mouse;
  }
  if (panning_) {
    if (ImGui::IsMouseDown(ImGuiMouseButton_Middle)) {
      interaction.cameraPanDelta = {mouse.x - panLastMouse_.x,
                                    mouse.y - panLastMouse_.y};
      panLastMouse_ = mouse;
    } else {
      panning_ = false;
    }
  }

  using Vertex = boost::graph_traits<Graph>::vertex_descriptor;
  std::vector<Vertex> vertices;
  const auto [vertexBegin, vertexEnd] = boost::vertices(graph);
  for (auto vertex = vertexBegin; vertex != vertexEnd; ++vertex)
    vertices.push_back(*vertex);

  const auto [edgeBegin, edgeEnd] = boost::edges(graph);
  std::set<std::pair<std::size_t, std::size_t>> drawnConnections;
  for (auto edge = edgeBegin; edge != edgeEnd; ++edge) {
    const Vertex sourceVertex = boost::source(*edge, graph);
    const Vertex targetVertex = boost::target(*edge, graph);
    const auto key = std::pair{static_cast<std::size_t>(sourceVertex),
                               static_cast<std::size_t>(targetVertex)};
    if (!drawnConnections.insert(key).second)
      continue;

    const auto sourcePoint = positions.find(graph[sourceVertex].id);
    const auto targetPoint = positions.find(graph[targetVertex].id);
    if (sourcePoint == positions.end() || targetPoint == positions.end())
      continue;

    const bool sourceMachine =
        graph[sourceVertex].type ==
        OpenPeripherals::Graph::PeripheralNodeType::Machine;
    const bool targetMachine =
        graph[targetVertex].type ==
        OpenPeripherals::Graph::PeripheralNodeType::Machine;
    const ImVec2 sourceSize(sourceMachine ? config_.machineWidth
                                          : config_.peripheralWidth,
                           sourceMachine ? config_.machineHeight
                                          : config_.peripheralHeight);
    const ImVec2 targetSize(targetMachine ? config_.machineWidth
                                          : config_.peripheralWidth,
                           targetMachine ? config_.machineHeight
                                          : config_.peripheralHeight);
    const ImVec2 scaledSourceSize(sourceSize.x * cameraZoom,
                                  sourceSize.y * cameraZoom);
    const ImVec2 scaledTargetSize(targetSize.x * cameraZoom,
                                  targetSize.y * cameraZoom);
    DrawEdge(drawList,
             ImVec2(center.x + cameraOffset.x + sourcePoint->second.x * cameraZoom,
                    center.y + cameraOffset.y + sourcePoint->second.y * cameraZoom),
             ImVec2(center.x + cameraOffset.x + targetPoint->second.x * cameraZoom,
                    center.y + cameraOffset.y + targetPoint->second.y * cameraZoom),
             scaledSourceSize, scaledTargetSize);
  }

  for (const Vertex vertex : vertices) {
    const auto &node = graph[vertex];
    const auto point = positions.find(node.id);
    if (point == positions.end())
      continue;

    const bool isMachine = node.type ==
                           OpenPeripherals::Graph::PeripheralNodeType::Machine;
    const ImVec2 size((isMachine ? config_.machineWidth : config_.peripheralWidth) * cameraZoom,
                      (isMachine ? config_.machineHeight : config_.peripheralHeight) * cameraZoom);
    const bool isSelected = selected == node.id;
    const ImU32 fill = isSelected ? config_.selectedColor
                                  : (isMachine ? config_.machineColor
                                               : config_.peripheralColor);
    const ImU32 outline = isSelected ? config_.selectedOutlineColor
                                     : config_.outlineColor;
    const NodeShape shape = isMachine ? config_.machineShape
                                      : config_.peripheralShape;
    const std::string label = node.name.empty()
                                  ? (isMachine ? "This machine" : "Peripheral")
                                  : node.name;
    const ImVec2 screenPoint(center.x + cameraOffset.x + point->second.x * cameraZoom,
                             center.y + cameraOffset.y + point->second.y * cameraZoom);
    DrawNode(drawList, screenPoint, size, shape, fill, outline, label,
             cameraZoom);

    const ImVec2 minimum(screenPoint.x - size.x * 0.5F,
                         screenPoint.y - size.y * 0.5F);
    const ImVec2 maximum(screenPoint.x + size.x * 0.5F,
                         screenPoint.y + size.y * 0.5F);
    if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) &&
        ImGui::IsMouseHoveringRect(minimum, maximum)) {
      interaction.clickedNode = node.id;
      draggingNode_ = node.id;
      dragStartMouse_ = ImGui::GetIO().MousePos;
      dragMoved_ = false;
    }
  }

  if (draggingNode_) {
    if (!positions.contains(*draggingNode_)) {
      draggingNode_.reset();
      dragMoved_ = false;
    } else if (ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
      const ImVec2 mouse = ImGui::GetIO().MousePos;
      const float dx = mouse.x - dragStartMouse_.x;
      const float dy = mouse.y - dragStartMouse_.y;
      if (dx * dx + dy * dy > 9.0F)
        dragMoved_ = true;
      if (dragMoved_) {
        const auto vertex = std::find_if(
            vertices.begin(), vertices.end(), [&](Vertex candidate) {
              return graph[candidate].id == *draggingNode_;
            });
        if (vertex == vertices.end()) {
          draggingNode_.reset();
          dragMoved_ = false;
          return interaction;
        }
        const auto &node = graph[*vertex];
        const bool isMachine = node.type ==
                               OpenPeripherals::Graph::PeripheralNodeType::Machine;
        interaction.draggedNode = draggingNode_;
        interaction.dragPosition = {
            (mouse.x - center.x - cameraOffset.x) / cameraZoom,
            (mouse.y - center.y - cameraOffset.y) / cameraZoom,
        };
      }
    } else {
      if (dragMoved_)
        interaction.dragEnded = draggingNode_;
      draggingNode_.reset();
      dragMoved_ = false;
    }
  }

  return interaction;
}

void PeripheralGraphRenderer::DrawEdge(ImDrawList *drawList, ImVec2 source,
                                       ImVec2 target, ImVec2 sourceSize,
                                       ImVec2 targetSize) const {
  const float dx = target.x - source.x;
  const float dy = target.y - source.y;
  const float length = std::sqrt(dx * dx + dy * dy);
  if (length < 1.0F)
    return;

  const float ux = dx / length;
  const float uy = dy / length;
  const auto rectRadius = [](float directionX, float directionY,
                             ImVec2 size) {
    const float xDistance = std::abs(directionX) < 1.0e-4F
                                ? std::numeric_limits<float>::infinity()
                                : size.x * 0.5F / std::abs(directionX);
    const float yDistance = std::abs(directionY) < 1.0e-4F
                                ? std::numeric_limits<float>::infinity()
                                : size.y * 0.5F / std::abs(directionY);
    return std::min(xDistance, yDistance);
  };
  const float sourceOffset = rectRadius(ux, uy, sourceSize);
  const float targetOffset = rectRadius(ux, uy, targetSize);
  const ImVec2 start(source.x + ux * sourceOffset,
                     source.y + uy * sourceOffset);
  const ImVec2 tip(target.x - ux * targetOffset,
                   target.y - uy * targetOffset);
  drawList->AddLine(start, tip, config_.edgeColor, 2.0F);
  DrawArrow(drawList, tip, ImVec2(ux, uy));
}

void PeripheralGraphRenderer::DrawArrow(ImDrawList *drawList, ImVec2 tip,
                                        ImVec2 direction) const {
  if (config_.arrowType == ArrowType::None)
    return;

  constexpr float length = 10.0F;
  constexpr float halfWidth = 5.0F;
  const ImVec2 base(tip.x - direction.x * length,
                    tip.y - direction.y * length);
  const ImVec2 normal(-direction.y, direction.x);
  const ImVec2 left(base.x + normal.x * halfWidth,
                    base.y + normal.y * halfWidth);
  const ImVec2 right(base.x - normal.x * halfWidth,
                     base.y - normal.y * halfWidth);
  if (config_.arrowType == ArrowType::Triangle) {
    drawList->AddTriangleFilled(tip, left, right, config_.edgeColor);
  } else {
    drawList->AddLine(tip, left, config_.edgeColor, 2.0F);
    drawList->AddLine(tip, right, config_.edgeColor, 2.0F);
  }
}

void PeripheralGraphRenderer::DrawNode(ImDrawList *drawList, ImVec2 center,
                                       ImVec2 size, NodeShape shape, ImU32 fill,
                                       ImU32 outline,
                                       const std::string &label,
                                       float zoom) const {
  const ImVec2 minimum(center.x - size.x * 0.5F,
                       center.y - size.y * 0.5F);
  const ImVec2 maximum(center.x + size.x * 0.5F,
                       center.y + size.y * 0.5F);
  const float rounding = shape == NodeShape::Rectangle ? 0.0F : 6.0F;
  drawList->AddRectFilled(minimum, maximum, fill, rounding);
  drawList->AddRect(minimum, maximum, outline, rounding, 0, 2.0F);

  const float padding = config_.textPadding * zoom;
  const float wrapWidth = std::max(1.0F, size.x - padding * 2.0F);
  const ImVec2 textSize = ImGui::CalcTextSize(label.c_str(), nullptr, false,
                                             wrapWidth / zoom);
  const ImVec2 scaledTextSize(textSize.x * zoom, textSize.y * zoom);
  const ImVec2 textPosition(center.x - scaledTextSize.x * 0.5F,
                            center.y - scaledTextSize.y * 0.5F);
  drawList->PushClipRect(
      ImVec2(minimum.x + padding,
             minimum.y + padding * 0.5F),
      ImVec2(maximum.x - padding,
             maximum.y - padding * 0.5F),
      true);
  drawList->AddText(ImGui::GetFont(), ImGui::GetFontSize() * zoom, textPosition,
                    config_.labelColor,
                    label.c_str(), nullptr, wrapWidth);
  drawList->PopClipRect();
}

} // namespace PeripheralViewer
