#pragma once


#include "OpenPeripherals/Core/Discovery/Endpoint.hpp"
#include "OpenPeripherals/Core/Types.hpp"

#include <boost/graph/adjacency_list.hpp>

#include <optional>
#include <unordered_map>
#include <vector>

namespace OpenPeripherals {
namespace Graph {

struct PeripheralVertex {
  PeripheralID id;
};
using EdgeID = std::uint32_t;
struct PeripheralEdge {
  EdgeID id;

  // No from/to needed: Boost stores topology.
  Endpoint endpoint;
};

class PeripheralGraph {
public:
  using Graph = boost::adjacency_list<boost::listS,     // Edge storage
                                      boost::vecS,      // Vertex storage
                                      boost::directedS, // Directed connections
                                      PeripheralVertex, // Vertex properties
                                      PeripheralEdge    // Edge properties
                                      >;

  using Vertex = boost::graph_traits<Graph>::vertex_descriptor;
  using Edge = boost::graph_traits<Graph>::edge_descriptor;

  PeripheralGraph() = default;

  Vertex AddPeripheral(PeripheralID id) {
    if (auto it = vertices_.find(id); it != vertices_.end())
      return it->second;

    auto vertex = boost::add_vertex(PeripheralVertex{id}, graph_);

    vertices_.emplace(id, vertex);
    return vertex;
  }

  Edge AddConnection(PeripheralID from, PeripheralID to, EdgeID edgeID,
                     Endpoint endpoint) {
    const auto source = AddPeripheral(from);
    const auto target = AddPeripheral(to);

    auto [edge, inserted] = boost::add_edge(
        source, target,
        PeripheralEdge{.id = edgeID, .endpoint = std::move(endpoint)}, graph_);

    return edge;
  }

  [[nodiscard]]
  std::optional<Vertex> FindPeripheral(PeripheralID id) const {
    auto it = vertices_.find(id);

    if (it == vertices_.end())
      return std::nullopt;

    return it->second;
  }

  [[nodiscard]]
  const Graph &GetGraph() const noexcept {
    return graph_;
  }

  [[nodiscard]]
  std::vector<std::vector<PeripheralID>> FindAllPaths(PeripheralID from,
                                                      PeripheralID to) const {
    std::vector<std::vector<PeripheralID>> paths;

    const auto source = FindPeripheral(from);
    const auto target = FindPeripheral(to);

    if (!source || !target)
      return paths;

    std::vector<bool> visited(boost::num_vertices(graph_), false);
    std::vector<PeripheralID> currentPath;

    auto output = std::back_inserter(paths);

    auto dfs = [&](auto &&self, Vertex vertex) -> void {
      visited[vertex] = true;
      currentPath.push_back(graph_[vertex].id);

      if (vertex == *target) {
        *output++ = currentPath;
      } else {
        auto [begin, end] = boost::out_edges(vertex, graph_);

        for (auto it = begin; it != end; ++it) {
          const Vertex next = boost::target(*it, graph_);

          if (!visited[next])
            self(self, next);
        }
      }

      currentPath.pop_back();
      visited[vertex] = false;
    };

    dfs(dfs, *source);
    return paths;
  }

private:
  Graph graph_;

  std::unordered_map<PeripheralID, Vertex> vertices_;
};
class PeripheralRouteGraph {
public:
  PeripheralRouteGraph(PeripheralID source, PeripheralID destination,
                       PeripheralGraph graph)
      : source_(source), destination_(destination), graph_(std::move(graph)) {}
  [[nodiscard]] PeripheralID GetSource() const noexcept { return source_; }

  [[nodiscard]] PeripheralID GetDestination() const noexcept {
    return destination_;
  }
  [[nodiscard]] const PeripheralGraph &GetGraph() const noexcept {
    return graph_;
  }
  [[nodiscard]] std::vector<std::vector<PeripheralID>> FindAllPaths() const {
    return graph_.FindAllPaths(source_, destination_);
  }
  // Add methods for managing peripheral routes here
private:
  PeripheralID source_;
  PeripheralID destination_;
  PeripheralGraph graph_;
};
} // namespace Graph
} // namespace OpenPeripherals