#include "Graph.h"

#include "DisjointSet.h"

#include <algorithm>
#include <iterator>
#include <cassert>

namespace QApp {
namespace Kernel {

Graph::Graph() {
  for (int i = 0; i < 6; ++i)
    addVertex(i);


  addEdge({0, 1, 19});
  addEdge({0, 2, 28});
  addEdge({0, 3, 34});
  addEdge({0, 4, 21});
  addEdge({0, 5, 45});

  addEdge({1, 2, 18});
  addEdge({1, 3, 25});
  addEdge({1, 4, 26});
  addEdge({1, 5, 27});

  addEdge({2, 3, 17});
  addEdge({2, 4, 28});
  addEdge({2, 5, 30});

  addEdge({3, 4, 16});
  addEdge({3, 5, 28});

  addEdge({4, 5, 15});
}

void Graph::addEdge(Edge e) {
  assert(AdjLists_.count(e.u) == 1);
  assert(AdjLists_.count(e.v) == 1);
  auto p = adjacent(e.u).insert({e.v, e.w});
  if (p.second) {
    adjacent(e.v).insert({e.u, e.w});
    CountEdges_ += 1;
  }
}

void Graph::removeEdge(Edge e) {
  assert(AdjLists_.count(e.u) == 1);
  assert(AdjLists_.count(e.v) == 1);
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

void Graph::addVertex(VertexId u) {
  assert(AdjLists_.count(u) == 0);
  AdjLists_.emplace(u, AdjacentEdges{});
}

void Graph::removeVertex(VertexId u) {
  for (OutEdge e : adjacent(u)) {
    AdjLists_[e.v].erase({u, e.w});
  }

  CountEdges_ -= adjacent(u).size();
  AdjLists_.erase(u);
}

size_t Graph::getVerticesCount() const {
  return AdjLists_.size();
}

int Graph::getCountEdges() const {
  return CountEdges_;
}

Graph::SortedEdges Graph::getSortedEdges() const {
  SortedEdges sortedEdges;
  for (const auto &[v, outEdges] : AdjLists_) {
    auto st = outEdges.upper_bound({v, 0});
    auto end = outEdges.end();
    auto convertOutEdge = [&u = v](OutEdge e) { return Edge{u, e.v, e.w}; };
    std::transform(st, end, std::back_inserter(sortedEdges), convertOutEdge);
  }
  std::ranges::sort(sortedEdges, {}, &Edge::w);

  assert(ssize(sortedEdges) == CountEdges_
         && "List of sorted edges by weight contains not all edges");
  return sortedEdges;
}

Graph::AdjacentEdges &Graph::adjacent(VertexId v) {
  assert(AdjLists_.count(v) == 1);
  return AdjLists_.find(v)->second;
}

const Graph::AdjacentEdges &Graph::adjacent(VertexId v) const {
  assert(AdjLists_.count(v) == 1);
  return AdjLists_.find(v)->second;
}

} // namespace Kernel
} // namespace QApp
