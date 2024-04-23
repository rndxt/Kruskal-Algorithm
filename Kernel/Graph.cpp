#include "Graph.h"

#include <algorithm>
#include <cassert>
#include <iterator>

namespace QApp {
namespace Kernel {

void Graph::addEdge(Edge e) {
  assert(AdjLists_.contains(e.u));
  assert(AdjLists_.contains(e.v));
  auto p = adjacent(e.u).insert({e.v, e.w});
  if (p.second) {
    adjacent(e.v).insert({e.u, e.w});
    CountEdges_ += 1;
  }
}

void Graph::removeEdge(Edge e) {
  assert(AdjLists_.contains(e.u));
  assert(AdjLists_.contains(e.v));
  AdjacentEdges &outEdgesU = adjacent(e.u);
  AdjacentEdges &outEdgesV = adjacent(e.v);

  assert(outEdgesU.count({e.v, e.w}) == outEdgesV.count({e.u, e.w})
         && "Wrong invariant of class");

  auto it = outEdgesU.find({e.v, e.w});
  if (it != end(outEdgesU)) {
    outEdgesU.erase(it);
    outEdgesV.erase(outEdgesV.find({e.u, e.w}));
    CountEdges_ -= 1;
  }
}

void Graph::addVertex(VertexId vertexId) {
  assert(!AdjLists_.contains(vertexId));
  AdjLists_.emplace(vertexId, AdjacentEdges{});
}

void Graph::removeVertex(VertexId vertexId) {
  for (OutEdge e : adjacent(vertexId)) {
    AdjLists_[e.v].erase({vertexId, e.w});
  }

  CountEdges_ -= adjacent(vertexId).size();
  AdjLists_.erase(vertexId);
}

size_t Graph::getVerticesCount() const {
  return AdjLists_.size();
}

size_t Graph::getCountEdges() const {
  return CountEdges_;
}

Graph::AdjacentEdges &Graph::adjacent(VertexId vertexId) {
  assert(AdjLists_.contains(vertexId));
  return AdjLists_.find(vertexId)->second;
}

const Graph::AdjacentEdges &Graph::adjacent(VertexId vertexId) const {
  assert(AdjLists_.contains(vertexId));
  return AdjLists_.find(vertexId)->second;
}

} // namespace Kernel
} // namespace QApp
