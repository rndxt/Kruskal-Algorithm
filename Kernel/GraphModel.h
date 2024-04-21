#pragma once

#include "Graph.h"
#include "QObserver.h"

#include <optional>

namespace QApp {
namespace Kernel {

class GraphModel {
  using GraphData = std::optional<Graph>;
  using ObservableGraph = Library::CObservable<GraphData>;
  using ObserverGraph= Library::CObserver<GraphData>;

public:
  GraphModel();

  void subscribe(ObserverGraph* obs);

private:
  GraphData graph_;
  ObservableGraph port_ = [this]() -> const GraphData& { return graph_; };
};

} // namespace Kernel
} // namespace QApp

