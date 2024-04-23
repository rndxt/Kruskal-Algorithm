#pragma once

#include "Algorithm.h"
#include "AlgorithmAction.h"
#include "AlgorithmAnimator.h"
#include "DrawData.h"
#include "MouseAction.h"
#include "NodeAnimator.h"
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
  void handleSliderAction(int value);

private:
  void onMousePress_(const QPointF& position);
  void onMouseMove_(const QPointF& position);
  void onMouseRelease_(const QPointF& position);
  void onAnimationStep();
  void onAnimationNode(const DrawData::DrawNode& node1,
                       const DrawData::DrawNode& node2);
  void onAlgorithmData(AlgorithmData&& data);
  void onNextStepData(AlgorithmData&& data);

  int touchedItem_(const QPointF& position) const;

  static constexpr int k_non = -1;

  Data data_;
  Palette palette_;
  NodeAnimator node_animator_;
  AlgorithmAnimator algorithm_animator_;
  int active_index_ = k_non;
  QPointF diff_ = {0., 0.};
  QColor prevContur_ = Qt::black;
  Observable port_ = [this]() -> const Data& { return data_; };
  ObserverAlgorithm in_port_;
  ObserverAlgorithm next_step_port_;
  ObservableAction action_port_;
};

} // namespace Kernel
} // namespace QApp
