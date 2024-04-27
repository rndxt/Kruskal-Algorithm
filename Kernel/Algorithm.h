#pragma once

#include "DisjointSet.h"
#include "EdgeStatus.h"
#include "Graph.h"

namespace QApp {
namespace Kernel {

class Algorithm {
public:
  using Edge = Graph::Edge;

  struct EdgeWithStatus {
    Edge edge;
    EdgeStatus status;
  };

  Algorithm() = default;

  const Graph& graph() const;
  const DisjointSet& dsu() const;
  const std::vector<EdgeWithStatus>& edgesWithInfo() const;
  void doNextStep();
  void replaceModel(const std::vector<std::vector<int>>& newModel);

  static Algorithm defaultExample();

private:
  void buildModelByEdges(int countVertices, const std::vector<Edge>& edges);

  size_t step_ = 0;
  Graph graph_;
  std::vector<EdgeWithStatus> sortedEdges_;
  DisjointSet dsu_;
};

} // namespace Kernel
} // namespace QApp
