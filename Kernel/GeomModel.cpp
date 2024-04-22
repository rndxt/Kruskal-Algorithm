#include "GeomModel.h"

#include <QDebug>

#include <cassert>
#include <ranges>
#include <numbers>

namespace QApp {
namespace Kernel {

GeomModel::GeomModel()
    : active_animator_([this](int vertexId, const DrawData::DrawEdge& edge, const DrawData::DrawChangesTable& changes) { onActiveAnimation_(vertexId, edge, changes); }),
      in_port_([this](GraphData&& data) { onFieldData(std::move(data)); }) {
}

GeomModel::ObserverField* GeomModel::port() {
  return &in_port_;
}

void GeomModel::subscribeToDrawData(Observer* obs) {
  assert(obs);
  port_.subscribe(obs);
}

void GeomModel::subscribeToItemAction(ObserverAction* obs) {
  assert(obs);
  action_port_.subscribe(obs);
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
  case QApp::Kernel::EButtonStatus::RunAnimation:
    active_animator_.startAnimation(graph_);
    break;
  case QApp::Kernel::EButtonStatus::PauseAnimation:
    active_animator_.pauseAnimation();
    break;
  default:
    assert(false);
    break;
  }
}

void GeomModel::onMousePress_(const QPointF& position) {
  assert(data_.has_value());

  int vertexId = touchedItem_(position);
  if (vertexId == k_non)
    return;

  active_index_ = vertexId;
  diff_ = position - data_->nodes[active_index_].center;
  data_->nodes[active_index_].contur = palette_.countur(ItemStatus::Active);
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

  data_->nodes[active_index_].contur = palette_.countur(ItemStatus::Inactive);
  port_.notify();
  diff_ = {0., 0.};
  active_index_ = k_non;
}

void GeomModel::onActiveAnimation_(int vertexId,
                                   const DrawData::DrawEdge& drawEdge,
                                   const DrawData::DrawChangesTable& drawTable) {
  assert(data_.has_value());
  assert(data_->nodes.contains(vertexId));
  for (auto [vertex, index] : drawTable) {
    data_->table[vertex] = index;
  }

  data_->nodes[vertexId].contur = QColor("orange");
  data_->nodes[drawEdge.vertexId].contur = QColor("orange");
  auto it = std::ranges::lower_bound(data_->edges[vertexId], drawEdge.vertexId,
                                     {}, &DrawData::DrawEdge::vertexId);
  assert(it != end(data_->edges[vertexId]));
  it->contur = drawEdge.contur;
  port_.notify();
}

void GeomModel::onFieldData(GraphData&& data) {
  qDebug() << "GeomModel::onFieldData";
  if (!data.has_value()) {
    if (data_.has_value()) {
      data_.reset();
      port_.notify();
    }
    return;
  }

  if (!data_.has_value())
    data_.emplace();

  graph_ = *data;
  size_t countVertices = graph_.getVerticesCount();

  for (int i = 0; i < countVertices; ++i) {
    data_->table.insert({i, i});
  }

  double xc = 400.;
  double yc = 300.;
  double R = 100;
  int i = 0;
  for (auto vertex : std::views::keys(graph_.AdjLists_)) {
    double angle = 2 * std::numbers::pi * i / countVertices;
    QPointF center = {xc + R * std::cos(angle), yc + R * std::sin(angle)};
    i += 1;
    data_->nodes.insert({vertex, DrawData::DrawNode{center, 10, Qt::black, vertex}});
  }

  for (const auto &[vertex, outEdges] : graph_.AdjLists_) {
    for (const auto &outEdge : outEdges) {
      data_->edges[vertex].emplace_back(outEdge.v, outEdge.w, Qt::black);
    }
  }
  port_.notify();
}

int GeomModel::touchedItem_(const QPointF& position) const {
  assert(data_.has_value());
  for (const auto &drawNode : std::views::values(data_->nodes)) {
    QPointF diff = drawNode.center - position;
    if (std::sqrt(QPointF::dotProduct(diff, diff)) < drawNode.radius) {
      return drawNode.id;
    }
  }
  return k_non;
}

} // namespace Kernel
} // namespace QApp
