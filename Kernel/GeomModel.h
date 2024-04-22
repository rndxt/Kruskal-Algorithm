#pragma once

#include "DrawData.h"
#include "Graph.h"
#include "ItemAction.h"
#include "MouseAction.h"
#include "Palette.h"
#include "QObserver.h"

#include <optional>

namespace QApp {
namespace Kernel {

class GeomModel {
  using Data = std::optional<DrawData>;
  using Observable = Library::CObservable<Data>;
  using Observer = Library::CObserver<Data>;

  using GraphData = std::optional<Graph>;
  using ObserverField = Library::CObserver<GraphData>;

  using ItemData = std::optional<ItemAction>;
  using ObservableAction = Library::CObservableDataMono<ItemData>;
  using ObserverAction = Library::CObserver<ItemData>;

public:
  GeomModel();

  ObserverField* port();
  void subscribeToDrawData(Observer* obs);
  void subscribeToItemAction(ObserverAction* obs);

  void handleMouseAction(const MouseAction& action);

private:
  void onMousePress_(const QPointF& position);
  void onMouseMove_(const QPointF& position);
  void onMouseRelease_(const QPointF& position);
  void onFieldData(GraphData&& data);

  int touchedItem_(const QPointF& position) const;

  static constexpr int k_non = -1;

  Data data_;
  Palette palette_;
  int active_index_ = k_non;
  QPointF diff_ = {0., 0.};
  Observable port_ = [this]() -> const Data& { return data_; };
  ObserverField in_port_;
  ObservableAction action_port_;
};

} // namespace Kernel
} // namespace QApp
