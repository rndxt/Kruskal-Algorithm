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

  using ModelData = std::optional<std::vector<std::vector<int>>>;
  using ObservableModel = Library::CObservableDataMono<ModelData>;
  using ObserverModel = Library::CObserver<ModelData>;

public:
  GeomModel();

  ObserverAlgorithm* port();
  ObserverAlgorithm* nextStepPort();

  void subscribeToDrawData(Observer* obs);
  void subscribeToItemAction(ObserverAction* obs);
  void subscribeToNewModel(ObserverModel* obs);

  void handleMouseAction(const MouseAction& action);
  void handleButtonAction(const ButtonAction& action);
  void handleSliderAction(int value);
  void handleReprAction(const std::vector<std::vector<int>>& action);

  void onMousePress_(const QPointF& position);
  void onMouseMove_(const QPointF& position);
  void onMouseRelease_(const QPointF& position);
  void onAnimationStep();
  void onAnimationNode(const DrawNode& node1, const DrawNode& node2);
  void onAlgorithmData(AlgorithmData&& data);
  void onNextStepData(AlgorithmData&& data);

private:
  int touchedNode_(const QPointF& position) const;

  static constexpr int k_non = -1;

  Data data_;
  Palette palette_;
  NodeAnimator node_animator_;
  AlgorithmAnimator algorithm_animator_;
  int active_index_ = k_non;
  QPointF diff_ = {0., 0.};
  QColor prevContur_ = Qt::black;
  Observable port_;
  ObserverAlgorithm in_port_;
  ObserverAlgorithm next_step_port_;
  ObservableAction action_port_;
  ObservableModel new_model_port_;
};

} // namespace Kernel
} // namespace QApp
