#pragma once

#include "Algorithm.h"
#include "AlgorithmAction.h"
#include "DrawData.h"
#include "ItemAnimator.h"
#include "MouseAction.h"
#include "Palette.h"
#include "QObserver.h"

#include <optional>

namespace QApp {
namespace Kernel {

class GeomModel {
  using DrawNode = DrawData::DrawNode;
  using DrawEdge = DrawData::DrawEdge;

  using Data = std::optional<DrawData>;
  using Observable = Library::CObservable<Data>;
  using Observer = Library::CObserver<Data>;

  using AlgorithmData = std::optional<Algorithm>;
  using ObserverAlgorithm = Library::CObserver<AlgorithmData>;

  using ItemData = std::optional<ItemAction>;
  using ObservableAction = Library::CObservableDataMono<ItemData>;
  using ObserverAction = Library::CObserver<ItemData>;

public:
  GeomModel();

  ObserverAlgorithm* port();
  ObserverAlgorithm* nextStepPort();
  void subscribeToDrawData(Observer* obs);
  void subscribeToItemAction(ObserverAction* obs);

  void handleMouseAction(const MouseAction& action);
  void handleButtonAction(const ButtonAction& action);

private:
  void onMousePress_(const QPointF& position);
  void onMouseMove_(const QPointF& position);
  void onMouseRelease_(const QPointF& position);
  // void onActiveAnimation_(int vertexId, const DrawData::DrawEdge& drawEdge,
  // const DrawData::DrawChangesTable& drawChanges);
  void onAnimationDsuLabel(const DrawData::DrawLabelInfo labelInfo);
  void onAlgorithmData(AlgorithmData&& data);
  void onNextStepData(AlgorithmData&& data);

  int touchedItem_(const QPointF& position) const;

  static constexpr int k_non = -1;

  Data data_;
  Palette palette_;
  LabelAnimator label_animator_;
  int active_index_ = k_non;
  QPointF diff_ = {0., 0.};
  Observable port_ = [this]() -> const Data& { return data_; };
  ObserverAlgorithm in_port_;
  ObserverAlgorithm next_step_port_;
  ObservableAction action_port_;
};

} // namespace Kernel
} // namespace QApp
