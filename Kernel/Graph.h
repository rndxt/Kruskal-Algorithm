#pragma once

#include <set>
#include <unordered_map>

namespace QApp {
namespace Kernel {

class Graph {
public:
  using VertexId = int;
  using Weight = int;

  struct Edge {
    VertexId u;
    VertexId v;
    Weight w;
  };

  Graph() = default;

  void addEdge(Edge e);
  void removeEdge(Edge e);

  void addVertex(VertexId u);
  void removeVertex(VertexId u);

  size_t getVerticesCount() const;
  size_t getCountEdges() const;

  struct OutEdge {
    VertexId v;
    Weight w;

    friend bool operator<(const OutEdge& lhs, const OutEdge& rhs) {
      return lhs.v < rhs.v;
    }
  };

  using AdjacentEdges = std::set<OutEdge>;
  using Container = std::unordered_map<VertexId, AdjacentEdges>;

  AdjacentEdges &adjacent(VertexId v);
  const AdjacentEdges &adjacent(VertexId v) const;

  Container AdjLists_;
  size_t CountEdges_ = 0;
};

} // namespace Kernel
} // namespace QApp
