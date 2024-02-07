#include "Graph.h"

#include "DisjointSet.h"

#include <algorithm>
#include <cassert>

namespace NSProject {

Graph::Graph(size_t V) : AdjLists_(V) {}

void Graph::addEdge(Edge e) {
  auto [u, v, w] = e;
  assert(u < AdjLists_.size());
  assert(v < AdjLists_.size());
  adjacent(u).emplace(v, w);
  adjacent(v).emplace(u, w);
  E_ += 1;
}

Graph::AdjacentList &Graph::adjacent(Vertex u) {
  assert(u < getCountVertex());
  return AdjLists_[u];
}

const Graph::AdjacentList &Graph::adjacent(Vertex u) const {
  assert(u < getCountVertex());
  return AdjLists_[u];
}

void Graph::removeEdge(Edge e) {
  auto [u, v, w] = e;
  assert(u < getCountVertex());
  assert(v < getCountVertex());
  AdjacentList &ListU = adjacent(u);
  AdjacentList &ListV = adjacent(v);

  assert(ListU.count({v, w}) == ListV.count({u, w})
         && "Wrong invariant of class");

  auto it = ListU.find({v, w});
  if (it != ListU.end()) {
    ListU.erase(it);
    ListV.erase(ListV.find({u, w}));
    E_ -= 1;
  }
}

Graph::EdgesList Graph::getSortedEdges() const {
  EdgesList list;
  for (Vertex u = 0; u < getCountVertex(); ++u) {
    auto it = adjacent(u).upper_bound({u, 0});
    for (; it != adjacent(u).end(); ++it) {
      list.insert({u, it->first, it->second});
    }
  }

  assert(list.size() == E_
         && "List of sorted edges by weight contains not all edges");
  assert(std::is_sorted(list.begin(), list.end()) && "Edges is not sorted");
  return list;
}

Graph Graph::getMST() const {
  auto V = getCountVertex();
  Graph MST(V);
  DisjointSet DSU(V);
  EdgesList sortedEdges = getSortedEdges();

  for (auto [u, v, w] : sortedEdges) {
    if (DSU.find(u) != DSU.find(v)) {
      MST.addEdge({u, v, w});
      DSU.join(u, v);
    }
  }

  assert(MST.getCountEdges() == getCountVertex() - DSU.getCountSets()
         && "MST always contain a N-K edges (K = number connected components)");
  return MST;
}

size_t Graph::getCountVertex() const {
  return AdjLists_.size();
}

size_t Graph::getCountEdges() const {
  return E_;
}

} // namespace NSProject
