#pragma once

#include "DisjointSet.h"
#include "Graph.h"

namespace QApp {
namespace Kernel {

enum class EdgeStatus : int { InMst, NotInMst, Unknown };

class Algorithm {
public:
  using Edge = Graph::Edge;

  struct EdgeWithStatus {
    Edge edge;
    EdgeStatus status;
  };

  Algorithm();

  const Graph& graph() const;
  const DisjointSet& dsu() const;
  const std::vector<EdgeWithStatus>& edgesWithInfo() const;
  void doNextStep();

private:
  Graph graph_;
  std::vector<EdgeWithStatus> sortedEdges_;
  DisjointSet dsu_;
  size_t step_ = 0;
};

} // namespace Kernel
} // namespace QApp
