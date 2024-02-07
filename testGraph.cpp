#include "testGraph.h"

#include "Graph.h"

#include <cassert>
#include <vector>

namespace NSProject {

void NSTestsGraph::testEdgeOrdering() {
  Graph::Edge e1 = {0, 1, 1};
  Graph::Edge e2 = {1, 2, 2};
  assert(e1 < e2);
}

void NSTestsGraph::testDefaultGraph() {
  Graph G1;
  assert(G1.getCountVertex() == 0);
  assert(G1.getCountEdges() == 0);

  size_t n = 10;
  Graph G2(n);
  assert(G2.getCountVertex() == n);
  assert(G2.getCountEdges() == 0);
}

void NSTestsGraph::testAddEdge() {
  size_t n = 10;
  Graph G(n);

  size_t countEdges = 0;
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = i + 1; j < n; ++j) {
      G.addEdge({i, j, i + j});
      countEdges += 1;
    }
  }
  assert(G.getCountVertex() == n);
  assert(G.getCountEdges() == n * (n - 1) / 2);
}

void NSTestsGraph::testRemoveEdge() {
  size_t n = 10;
  Graph G2(n);

  for (size_t i = 0; i < n; ++i) {
    for (size_t j = i + 1; j < n; ++j) {
      G2.addEdge({i, j, i + j});
    }
  }

  for (size_t i = 0; i < n; ++i) {
    for (size_t j = i + 1; j < n; ++j) {
      G2.removeEdge({i, j, i + j});
    }
  }

  assert(G2.getCountEdges() == 0);
}

void NSTestsGraph::testMST() {
  using Edge = Graph::Edge;

  Graph G(8);
  std::vector<Edge> edges
      = {{0, 1, 5}, {0, 2, 8}, {0, 3, 1}, {1, 5, 4}, {2, 4, 5},
         {3, 5, 4}, {3, 7, 5}, {4, 7, 2}, {5, 6, 3}, {5, 7, 3}};

  for (Edge e : edges) {
    G.addEdge(e);
  }
  assert(G.getCountEdges() == 10);

  std::vector<Edge> expectedEdgesInMST
      = {{0, 3, 1}, {1, 5, 4}, {2, 4, 5}, {3, 5, 4},
         {4, 7, 2}, {5, 6, 3}, {5, 7, 3}};

  Graph MST = G.getMST();
  for (Edge e : expectedEdgesInMST) {
    MST.removeEdge(e);
  }
  assert(MST.getCountEdges() == 0);
}

} // namespace NSProject
