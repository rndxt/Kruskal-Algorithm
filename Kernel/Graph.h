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
    VertexId u, v;
    Weight w;

    friend bool operator<(const Edge &lhs, const Edge &rhs) {
      return lhs.w < rhs.w;
    }
  };

  Graph();

  void addEdge(Edge e);
  void removeEdge(Edge e);

  void addVertex(VertexId u);
  void removeVertex(VertexId u);

  size_t getVerticesCount() const;
  int getCountEdges() const;

  struct OutEdge {
    VertexId v;
    Weight w;

    friend bool operator<(const OutEdge &lhs, const OutEdge &rhs) {
      return lhs.v < rhs.v;
    }
  };

  using AdjacentEdges = std::set<OutEdge>;
  using Container = std::unordered_map<VertexId, AdjacentEdges>;
  using SortedEdges = std::vector<Edge>;

  SortedEdges getSortedEdges() const;
  AdjacentEdges &adjacent(VertexId v);
  const AdjacentEdges &adjacent(VertexId v) const;

  Container AdjLists_;
  int CountEdges_ = 0;
};

} // namespace Kernel
} // namespace QApp
