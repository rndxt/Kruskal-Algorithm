#include "Algorithm.h"

#include <algorithm>
#include <cassert>
#include <iterator>

namespace QApp {
namespace Kernel {

Algorithm::Algorithm() {
  for (int i = 0; i < 6; ++i) {
    graph_.addVertex(i);
    dsu_.makeSet(i);
  }

  std::vector<Edge> edges
      = {{0, 1, 16}, {0, 2, 28}, {0, 3, 34}, {0, 4, 21}, {0, 5, 45},
         {1, 2, 18}, {1, 3, 25}, {1, 4, 26}, {1, 5, 27}, {2, 3, 17},
         {2, 4, 28}, {2, 5, 30}, {3, 4, 19}, {3, 5, 28}, {4, 5, 15}};

  for (auto edge : edges) {
    graph_.addEdge(edge);
  }

  for (const auto& [v, outEdges] : graph_.AdjLists_) {
    std::transform(
        outEdges.upper_bound({v, 0}), end(outEdges),
        std::back_inserter(sortedEdges_), [&u = v](Graph::OutEdge e) {
          return EdgeWithStatus{Edge{u, e.v, e.w}, EdgeStatus::Unknown};
        });
  }
  std::ranges::sort(
      sortedEdges_,
      [](const Edge& lhs, const Edge& rhs) { return lhs.w < rhs.w; },
      &EdgeWithStatus::edge);

  assert(size(sortedEdges_) == graph_.CountEdges_
         && "List of sorted edges by weight contains not all edges");
}

const Graph& Algorithm::graph() const {
  return graph_;
}

const DisjointSet& Algorithm::dsu() const {
  return dsu_;
}

const std::vector<Algorithm::EdgeWithStatus>& Algorithm::edgesWithInfo() const {
  return sortedEdges_;
}

void Algorithm::doNextStep() {
  if (step_ >= graph_.getCountEdges())
    return;

  EdgeWithStatus& e = sortedEdges_[step_++];
  e.status = EdgeStatus::NotInMst;

  if (dsu_.findSet(e.edge.u) != dsu_.findSet(e.edge.v)) {
    dsu_.join(e.edge.u, e.edge.v);
    e.status = EdgeStatus::InMst;
  }
}

} // namespace Kernel
} // namespace QApp