#include "Algorithm.h"

#include <algorithm>
#include <cassert>
#include <iterator>

namespace QApp {
namespace Kernel {

const Graph& Algorithm::graph() const {
  return graph_;
}

const DisjointSet& Algorithm::dsu() const {
  return dsu_;
}

const std::vector<Algorithm::EdgeWithStatus>& Algorithm::edgesWithStatus() const {
  return sortedEdges_;
}

void Algorithm::doNextStep() {
  if (step_ >= graph_.getCountEdges())
    return;

  EdgeWithStatus& e = sortedEdges_[step_++];
  e.status = EdgeStatus::NotInMst;

  if (dsu_.find(e.edge.u) != dsu_.find(e.edge.v)) {
    dsu_.join(e.edge.u, e.edge.v);
    e.status = EdgeStatus::InMst;
  }
}

void Algorithm::replaceModel(const std::vector<std::vector<int>>& newModel) {
  step_ = 0;
  dsu_.clear();
  graph_.clear();
  sortedEdges_.clear();

  assert(newModel.size() > 1);
  assert(newModel[0].size() == 2);

  int verticies = newModel[0][0];
  int countEdges = newModel[0][1];
  for (int i = 0; i < verticies; ++i) {
    graph_.addVertex(i);
    dsu_.makeSet(i);
  }

  sortedEdges_.reserve(countEdges);
  for (size_t i = 1; i < newModel.size(); ++i) {
    assert(newModel[i].size() == 3);
    Edge edge = {newModel[i][0], newModel[i][1], newModel[i][2]};
    graph_.addEdge(edge);
    sortedEdges_.emplace_back(edge, EdgeStatus::Unknown);
  }

  std::ranges::sort(
      sortedEdges_,
      [](const Edge& lhs, const Edge& rhs) { return lhs.w < rhs.w; },
      &EdgeWithStatus::edge);

  assert(graph_.getCountEdges() == sortedEdges_.size());
}

Algorithm Algorithm::defaultExample() {
  std::vector<Edge> edges
      = {{0, 1, 16}, {0, 2, 28}, {0, 3, 34}, {0, 4, 21}, {0, 5, 45},
         {1, 2, 18}, {1, 3, 25}, {1, 4, 26}, {1, 5, 27}, {2, 3, 17},
         {2, 4, 28}, {2, 5, 30}, {3, 4, 19}, {3, 5, 28}, {4, 5, 15}};
  Algorithm example;
  example.buildModelByEdges(6, edges);
  return example;
}

void Algorithm::buildModelByEdges(int countVertices,
                                  const std::vector<Edge>& edges) {
  for (int i = 0; i < countVertices; ++i) {
    graph_.addVertex(i);
    dsu_.makeSet(i);
  }

  for (auto edge : edges) {
    graph_.addEdge(edge);
    sortedEdges_.emplace_back(edge, EdgeStatus::Unknown);
  }

  std::ranges::sort(
      sortedEdges_,
      [](const Edge& lhs, const Edge& rhs) { return lhs.w < rhs.w; },
      &EdgeWithStatus::edge);

  assert(size(sortedEdges_) == graph_.getCountEdges()
         && "List of sorted edges by weight contains not all edges");
}

} // namespace Kernel
} // namespace QApp
