#pragma once

#include <OpenPeripherals/Core/PeripheralGraph.hpp>

#include <unordered_map>

namespace PeripheralViewer {

struct GraphPoint {
  float x{};
  float y{};
};

struct SpringLayoutConfig {
  float springLength{270.0F};
  float springStrength{0.35F};
  float repulsionStrength{240000.0F};
  float minimumNodeDistance{190.0F};
  float centerGravity{0.008F};
  float damping{0.97F};
  float maxSpeed{3000.0F};
  float maxForce{20000.0F};
  float simulationSpeed{16.0F};
  unsigned int solverSubsteps{8};
};

// Stateful force-directed layout. New nodes begin at the local origin and
// separate through the configured repulsion and spring forces.
class SpringGraphLayout {
public:
  using Graph = OpenPeripherals::Graph::PeripheralGraph::Graph;
  using Positions =
      std::unordered_map<OpenPeripherals::PeripheralID, GraphPoint>;

  SpringLayoutConfig &Config() noexcept { return config_; }
  const SpringLayoutConfig &Config() const noexcept { return config_; }

  const Positions &Update(const Graph &graph, float deltaSeconds);
  void MoveNode(const OpenPeripherals::PeripheralID &id, GraphPoint position,
                bool pin = true);
  void SetPinned(const OpenPeripherals::PeripheralID &id, bool pinned);
  void Reset() noexcept;

private:
  struct NodeState {
    GraphPoint position{};
    GraphPoint velocity{};
    bool pinned{false};
  };

  SpringLayoutConfig config_;
  std::unordered_map<OpenPeripherals::PeripheralID, NodeState> nodes_;
  Positions positions_;
};

} // namespace PeripheralViewer
