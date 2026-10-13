#include "GraphLayout.hpp"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <set>
#include <vector>

namespace PeripheralViewer {
namespace {

float ClampScale(float x, float y, float maximum) {
  const float magnitudeSquared = x * x + y * y;
  if (magnitudeSquared <= maximum * maximum || magnitudeSquared == 0.0F)
    return 1.0F;
  return maximum / std::sqrt(magnitudeSquared);
}

} // namespace

const SpringGraphLayout::Positions &SpringGraphLayout::Update(
    const Graph &graph, float deltaSeconds) {
  using Vertex = boost::graph_traits<Graph>::vertex_descriptor;
  std::vector<Vertex> vertices;
  std::unordered_map<OpenPeripherals::PeripheralID, std::size_t> indices;
  const auto [vertexBegin, vertexEnd] = boost::vertices(graph);
  for (auto vertex = vertexBegin; vertex != vertexEnd; ++vertex) {
    const auto &id = graph[*vertex].id;
    indices.emplace(id, vertices.size());
    vertices.push_back(*vertex);
    // Every node is born at (0, 0); repulsion separates the initial pile.
    nodes_.try_emplace(id, NodeState{});
  }

  for (auto it = nodes_.begin(); it != nodes_.end();) {
    if (!indices.contains(it->first))
      it = nodes_.erase(it);
    else
      ++it;
  }

  std::set<std::pair<std::size_t, std::size_t>> springPairs;
  const auto [edgeBegin, edgeEnd] = boost::edges(graph);
  for (auto edge = edgeBegin; edge != edgeEnd; ++edge) {
    const auto first = indices.at(graph[boost::source(*edge, graph)].id);
    const auto second = indices.at(graph[boost::target(*edge, graph)].id);
    if (first != second)
      springPairs.emplace(std::min(first, second), std::max(first, second));
  }

  if (vertices.empty()) {
    positions_.clear();
    return positions_;
  }

  const unsigned int substeps = std::max(1U, config_.solverSubsteps);
  const float simulationTime = std::clamp(deltaSeconds, 0.0F, 0.05F) *
                               std::max(0.0F, config_.simulationSpeed);
  const float dt = simulationTime / static_cast<float>(substeps);
  const float damping = std::pow(std::clamp(config_.damping, 0.0F, 1.0F),
                                 dt * 60.0F);
  for (unsigned int step = 0; step < substeps; ++step) {
    std::vector<GraphPoint> forces(vertices.size());

    // Pairwise inverse-square repulsion. If two fresh nodes overlap exactly,
    // derive a consistent direction from their IDs to break the symmetry.
    for (std::size_t first = 0; first < vertices.size(); ++first) {
      for (std::size_t second = first + 1; second < vertices.size(); ++second) {
        const auto &firstId = graph[vertices[first]].id;
        const auto &secondId = graph[vertices[second]].id;
        const auto &firstPosition = nodes_.at(firstId).position;
        const auto &secondPosition = nodes_.at(secondId).position;
        float dx = secondPosition.x - firstPosition.x;
        float dy = secondPosition.y - firstPosition.y;
        float distanceSquared = dx * dx + dy * dy;

        if (distanceSquared < 1.0e-4F) {
          const std::uint64_t seed =
              static_cast<std::uint64_t>(
                  std::hash<OpenPeripherals::PeripheralID>{}(firstId)) ^
              (static_cast<std::uint64_t>(
                   std::hash<OpenPeripherals::PeripheralID>{}(secondId))
               << 1);
          const float angle = static_cast<float>(seed % 628319ULL) / 100000.0F;
          dx = std::cos(angle);
          dy = std::sin(angle);
          distanceSquared = 1.0F;
        }

        const float distance = std::sqrt(distanceSquared);
        const float overlap =
            std::max(0.0F, config_.minimumNodeDistance - distance);
        const float magnitude = std::min(
            config_.maxForce,
            config_.repulsionStrength / distanceSquared +
                overlap * config_.springStrength * 8.0F);
        const float forceX = dx / distance * magnitude;
        const float forceY = dy / distance * magnitude;
        forces[first].x -= forceX;
        forces[first].y -= forceY;
        forces[second].x += forceX;
        forces[second].y += forceY;
      }
    }

    // One spring per node pair; multiple endpoint edges between the same two
    // peripherals should not multiply the layout force.
    for (const auto &[first, second] : springPairs) {
      const auto &firstId = graph[vertices[first]].id;
      const auto &secondId = graph[vertices[second]].id;
      const auto &firstPosition = nodes_.at(firstId).position;
      const auto &secondPosition = nodes_.at(secondId).position;
      const float dx = secondPosition.x - firstPosition.x;
      const float dy = secondPosition.y - firstPosition.y;
      const float distance = std::sqrt(dx * dx + dy * dy);
      if (distance < 1.0e-3F)
        continue;

      const float magnitude = config_.springStrength *
                              (distance - config_.springLength);
      const float forceX = dx / distance * magnitude;
      const float forceY = dy / distance * magnitude;
      forces[first].x += forceX;
      forces[first].y += forceY;
      forces[second].x -= forceX;
      forces[second].y -= forceY;
    }

    for (std::size_t index = 0; index < vertices.size(); ++index) {
      const auto &id = graph[vertices[index]].id;
      auto &state = nodes_.at(id);
      if (state.pinned) {
        state.velocity = {};
        continue;
      }
      forces[index].x -= state.position.x * config_.centerGravity;
      forces[index].y -= state.position.y * config_.centerGravity;

      const float forceScale = ClampScale(forces[index].x, forces[index].y,
                                          config_.maxForce);
      state.velocity.x =
          (state.velocity.x + forces[index].x * forceScale * dt) * damping;
      state.velocity.y =
          (state.velocity.y + forces[index].y * forceScale * dt) * damping;
      const float speedScale =
          ClampScale(state.velocity.x, state.velocity.y, config_.maxSpeed);
      state.velocity.x *= speedScale;
      state.velocity.y *= speedScale;

      state.position.x += state.velocity.x * dt;
      state.position.y += state.velocity.y * dt;
    }

    // Project overlaps apart after integration so minimumNodeDistance is an
    // actual spacing constraint, rather than only a soft force preference.
    const float minimumDistance =
        std::max(0.0F, config_.minimumNodeDistance);
    for (int pass = 0; pass < 2; ++pass) {
      for (std::size_t first = 0; first < vertices.size(); ++first) {
        for (std::size_t second = first + 1; second < vertices.size(); ++second) {
          const auto &firstId = graph[vertices[first]].id;
          const auto &secondId = graph[vertices[second]].id;
          auto &firstState = nodes_.at(firstId);
          auto &secondState = nodes_.at(secondId);
          if (firstState.pinned && secondState.pinned)
            continue;

          float dx = secondState.position.x - firstState.position.x;
          float dy = secondState.position.y - firstState.position.y;
          float distance = std::sqrt(dx * dx + dy * dy);
          if (distance >= minimumDistance)
            continue;

          if (distance < 1.0e-3F) {
            const std::uint64_t seed =
                static_cast<std::uint64_t>(
                    std::hash<OpenPeripherals::PeripheralID>{}(firstId)) ^
                (static_cast<std::uint64_t>(
                     std::hash<OpenPeripherals::PeripheralID>{}(secondId))
                 << 1);
            const float angle =
                static_cast<float>(seed % 628319ULL) / 100000.0F;
            dx = std::cos(angle);
            dy = std::sin(angle);
            distance = 0.0F;
          } else {
            dx /= distance;
            dy /= distance;
          }

          const float overlap = minimumDistance - distance;
          if (firstState.pinned) {
            secondState.position.x += dx * overlap;
            secondState.position.y += dy * overlap;
          } else if (secondState.pinned) {
            firstState.position.x -= dx * overlap;
            firstState.position.y -= dy * overlap;
          } else {
            firstState.position.x -= dx * overlap * 0.5F;
            firstState.position.y -= dy * overlap * 0.5F;
            secondState.position.x += dx * overlap * 0.5F;
            secondState.position.y += dy * overlap * 0.5F;
          }
        }
      }
    }
  }

  positions_.clear();
  for (const Vertex vertex : vertices) {
    const auto &id = graph[vertex].id;
    positions_.emplace(id, nodes_.at(id).position);
  }
  return positions_;
}

void SpringGraphLayout::Reset() noexcept {
  nodes_.clear();
  positions_.clear();
}

void SpringGraphLayout::MoveNode(
    const OpenPeripherals::PeripheralID &id, GraphPoint position, bool pin) {
  auto &state = nodes_[id];
  state.position = position;
  state.velocity = {};
  state.pinned = pin;
  positions_[id] = position;
}

void SpringGraphLayout::SetPinned(
    const OpenPeripherals::PeripheralID &id, bool pinned) {
  if (auto it = nodes_.find(id); it != nodes_.end()) {
    it->second.pinned = pinned;
    if (!pinned)
      it->second.velocity = {};
  }
}

} // namespace PeripheralViewer
