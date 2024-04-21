#pragma once

#include "DrawData.h"
#include "MouseAction.h"
#include "Palette.h"
#include "QObserver.h"
#include "Kernel/Graph.h"

#include <optional>

namespace QApp {
namespace Kernel {

class GraphGeomModel {
  using Data = std::optional<DrawGraph>;
  using Observable = Library::CObservable<Data>;
  using Observer = Library::CObserver<Data>;

public:
  GraphGeomModel(Graph &g);

  void handleMouseAction(const MouseAction& action);

private:
  void onMousePress_(const QPointF& position);
  void onMouseMove_(const QPointF& position);
  void onMouseRelease_(const QPointF& position);
  void onGraph(Graph& data);

  int touchedNode(const QPointF& position) const;

  static constexpr int k_non = -1;

  Data data_;
  Palette palette_;
  int active_index_ = k_non;
  QPointF diff_ = {0., 0.};
  Observable port_ = [this]() -> const Data& { return data_; };
};

} // namespace Kernel
} // namespace QApp
