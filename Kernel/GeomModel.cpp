#include "GeomModel.h"

#include <QDebug>

#include <cassert>
#include <ranges>
#include <numbers>

namespace QApp {
namespace Kernel {

GeomModel::GeomModel()
    : node_animator_([this](const DrawData::DrawNode& node1,
                            const DrawData::DrawNode& node2) {
        onAnimationNode(node1, node2);
      }),
      algorithm_animator_([this]() { onAnimationStep(); }),
      port_([this]() -> const Data& { return data_; }),
      in_port_(
          [this](AlgorithmData&& data) { onAlgorithmData(std::move(data)); }),
      next_step_port_(
          [this](AlgorithmData&& data) { onNextStepData(std::move(data)); }) {}

GeomModel::ObserverAlgorithm* GeomModel::port() {
  return &in_port_;
}

GeomModel::ObserverAlgorithm* GeomModel::nextStepPort() {
  return &next_step_port_;
}

void GeomModel::subscribeToDrawData(Observer* obs) {
  assert(obs);
  port_.subscribe(obs);
}

void GeomModel::subscribeToItemAction(ObserverAction* obs) {
  assert(obs);
  action_port_.subscribe(obs);
}

void GeomModel::subscribeToNewModel(ObserverModel* obs) {
  assert(obs);
  new_model_port_.subscribe(obs);
}

void GeomModel::handleMouseAction(const MouseAction& action) {
  if (!data_.has_value())
    return;

  QPointF local_position = action.position;
  switch (action.status) {
  case EMouseStatus::Pressed:
    onMousePress_(local_position);
    break;
  case EMouseStatus::Moved:
    onMouseMove_(local_position);
    break;
  case EMouseStatus::Released:
    onMouseRelease_(local_position);
    break;
  default:
    assert(false);
    break;
  }
}

void GeomModel::handleButtonAction(const ButtonAction& action) {
  if (!data_.has_value())
    return;

  switch (action.status) {
  case EButtonStatus::RunAnimation:
    action_port_.set(std::in_place_t(), 0, 0, 0);
    algorithm_animator_.startAnimation();
    break;
  case EButtonStatus::PauseAnimation:
    algorithm_animator_.pauseAnimation();
    break;
  default:
    assert(false);
    break;
  }
}

void GeomModel::handleSliderAction(int value) {
  if (!data_.has_value())
    return;
  algorithm_animator_.setSpeed(value);
}

void GeomModel::handleReprAction(const std::vector<std::vector<int>>& action) {
  if (!data_.has_value())
    return;
  new_model_port_.set(std::in_place_t(), action);
}

void GeomModel::onMousePress_(const QPointF& position) {
  assert(data_.has_value());

  int vertexId = touchedNode_(position);
  if (vertexId == k_non)
    return;

  active_index_ = vertexId;
  diff_ = position - data_->nodes[active_index_].center;
  prevContur_ = std::exchange(data_->nodes[active_index_].contur,
                              palette_.nodeCountur(NodeStatus::Active));
  port_.notify();
}

void GeomModel::onMouseMove_(const QPointF& position) {
  assert(data_.has_value());
  if (active_index_ == k_non)
    return;

  data_->nodes[active_index_].center = position - diff_;
  port_.notify();
}

void GeomModel::onMouseRelease_(const QPointF& position) {
  assert(data_.has_value());
  if (active_index_ == k_non)
    return;

  data_->nodes[active_index_].contur = prevContur_;
  port_.notify();
  diff_ = {0., 0.};
  active_index_ = k_non;
}

void GeomModel::onAnimationStep() {
  action_port_.notify();
}

void GeomModel::onAnimationNode(const DrawNode& node1, const DrawNode& node2) {
  data_->nodes[node1.id] = node1;
  data_->nodes[node2.id] = node2;
  port_.notify();
}

void GeomModel::onAlgorithmData(AlgorithmData&& data) {
  if (!data.has_value()) {
    if (data_.has_value()) {
      data_.reset();
      port_.notify();
    }
    return;
  }

  if (!data_.has_value())
    data_.emplace();

  data_->edges.clear();
  data_->nodes.clear();
  data_->table.clear();

  const Graph& graph = data->graph();
  const DisjointSet& dsu = data->dsu();

  for (int vertexId : graph.vertexView()) {
    data_->table.emplace_back(vertexId, dsu.find(vertexId));
  }

  size_t countVertices = graph.getVerticesCount();

  auto v = graph.vertexView() | std::views::enumerate;
  for (auto [i, vertex] : v) {
    double angle = 2 * std::numbers::pi * i / countVertices;
    QPointF center
        = {palette_.plot_center.x() + palette_.plot_radius * std::cos(angle),
           palette_.plot_center.y() + palette_.plot_radius * std::sin(angle)};
    data_->nodes.emplace(
        vertex, DrawNode{center, palette_.node_radius, Qt::black, vertex});
  }

  for (auto vertex : graph.vertexView()) {
    for (const auto& outEdge : graph.adjacent(vertex)) {
      data_->edges[vertex].emplace_back(outEdge.v, outEdge.w, Qt::black);
    }
  }

  port_.notify();
}

void GeomModel::onNextStepData(AlgorithmData&& data) {
  assert(data_.has_value());
  if (!data.has_value())
    return;

  const Graph& graph = data->graph();
  const DisjointSet& dsu = data->dsu();
  auto v = graph.vertexView() | std::views::enumerate;
  for (auto [i, vertexId] : v) {
    assert(data_->table[i].vertex == vertexId);
    data_->table[i].index = dsu.find(vertexId);
  }

  const auto& edgesWithStatus = data->edgesWithStatus();
  for (const auto& [edge, status] : edgesWithStatus) {
    auto it
        = std::ranges::find(data_->edges[edge.u], edge.v, &DrawEdge::vertexId);
    assert(it != end(data_->edges[edge.u]));
    QColor newStatus = palette_.edgeCountur(status);
    if (std::exchange(it->contur, newStatus) != newStatus) {
      node_animator_.startAnimation(data_->nodes[edge.u], data_->nodes[edge.v]);
    }

    auto it2
        = std::ranges::find(data_->edges[edge.v], edge.u, &DrawEdge::vertexId);
    assert(it2 != end(data_->edges[edge.v]));
    it2->contur = newStatus;
  }

  port_.notify();
}

int GeomModel::touchedNode_(const QPointF& position) const {
  assert(data_.has_value());
  auto v = std::views::values(data_->nodes);
  auto it = std::ranges::find_if(v, [position](const auto& drawNode) {
    QPointF diff = drawNode.center - position;
    return std::sqrt(QPointF::dotProduct(diff, diff)) < 10.;
  });

  if (it == end(v))
    return k_non;

  return (*it).id;
}

} // namespace Kernel
} // namespace QApp
