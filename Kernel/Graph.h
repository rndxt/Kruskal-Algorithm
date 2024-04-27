#pragma once

#include <ranges>
#include <set>
#include <unordered_map>

namespace QApp {
namespace Kernel {

class Graph {
public:
  using VertexId = int;
  using Weight = int;

private:
  struct OutEdge {
    VertexId v;
    Weight w;

    friend bool operator<(const OutEdge& lhs, const OutEdge& rhs) {
      return lhs.v < rhs.v;
    }
  };

  using AdjacentEdges = std::set<OutEdge>;
  using Container = std::unordered_map<VertexId, AdjacentEdges>;

public:
  using VertexView
      = std::ranges::keys_view<std::ranges::ref_view<const Container>>;

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

  VertexView vertexView() const;
  const AdjacentEdges& adjacent(VertexId v) const;
  void clear();

private:
  AdjacentEdges& adjacent(VertexId v);

  Container AdjLists_;
  size_t CountEdges_ = 0;
};

} // namespace Kernel
} // namespace QApp
