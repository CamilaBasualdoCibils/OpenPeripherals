#pragma once

#include "GraphLayout.hpp"

#include <imgui.h>

#include <optional>
#include <string>

namespace PeripheralViewer {

enum class ArrowType { Triangle, Chevron, None };
enum class NodeShape { Rectangle, RoundedRectangle };

struct GraphInteraction {
  std::optional<OpenPeripherals::PeripheralID> clickedNode;
  std::optional<OpenPeripherals::PeripheralID> draggedNode;
  GraphPoint dragPosition{};
  std::optional<OpenPeripherals::PeripheralID> dragEnded;
  GraphPoint cameraPanDelta{};
  GraphPoint cameraAnchor{};
  float cameraZoomFactor{1.0F};
};

struct GraphRenderConfig {
  ArrowType arrowType{ArrowType::Triangle};
  NodeShape peripheralShape{NodeShape::Rectangle};
  NodeShape machineShape{NodeShape::Rectangle};
  float peripheralWidth{176.0F};
  float peripheralHeight{76.0F};
  float machineWidth{184.0F};
  float machineHeight{80.0F};
  float textPadding{10.0F};
  bool pinAfterDrag{false};
  float minimumZoom{0.2F};
  float maximumZoom{3.0F};
  ImU32 backgroundColor{IM_COL32(20, 24, 32, 255)};
  ImU32 edgeColor{IM_COL32(113, 170, 228, 230)};
  ImU32 peripheralColor{IM_COL32(64, 83, 108, 255)};
  ImU32 machineColor{IM_COL32(88, 91, 140, 255)};
  ImU32 selectedColor{IM_COL32(64, 137, 218, 255)};
  ImU32 outlineColor{IM_COL32(140, 164, 195, 255)};
  ImU32 selectedOutlineColor{IM_COL32(180, 218, 255, 255)};
  ImU32 labelColor{IM_COL32(226, 231, 240, 255)};
};

// Draws graph edges and vertices. Arrow and node choices are configurable
// independently of both graph data and the force-directed layout.
class PeripheralGraphRenderer {
public:
  using Graph = SpringGraphLayout::Graph;
  using Positions = SpringGraphLayout::Positions;

  GraphRenderConfig &Config() noexcept { return config_; }
  const GraphRenderConfig &Config() const noexcept { return config_; }

  GraphInteraction
  Draw(ImDrawList *drawList, const Graph &graph, const Positions &positions,
       ImVec2 canvasMin, ImVec2 canvasMax,
       std::optional<OpenPeripherals::PeripheralID> selected,
       GraphPoint cameraOffset, float cameraZoom);

private:
  void DrawEdge(ImDrawList *drawList, ImVec2 source, ImVec2 target,
                ImVec2 sourceSize, ImVec2 targetSize) const;
  void DrawArrow(ImDrawList *drawList, ImVec2 tip, ImVec2 direction) const;
  void DrawNode(ImDrawList *drawList, ImVec2 center, ImVec2 size,
                NodeShape shape, ImU32 fill, ImU32 outline,
                const std::string &label, float zoom) const;

  GraphRenderConfig config_;
  std::optional<OpenPeripherals::PeripheralID> draggingNode_;
  ImVec2 dragStartMouse_{};
  bool dragMoved_{false};
  bool panning_{false};
  ImVec2 panLastMouse_{};
};

} // namespace PeripheralViewer
