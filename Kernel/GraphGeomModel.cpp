#include "GraphGeomModel.h"

#include <QDebug>
#include <QColor>

#include <cassert>
#include <ranges>
#include <numbers>

namespace QApp {
namespace Kernel {

GraphGeomModel::GraphGeomModel(Graph& g) {
  onGraph(g);
}

void GraphGeomModel::handleMouseAction(const MouseAction& action) {
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

void GraphGeomModel::onMousePress_(const QPointF& position) {
  // assert(data_.has_value());
  // int index = touchedItem_(position);
  // if (index != k_non) {
  //   active_index_ = index;
  //   diff_ = position - item_(active_index_).center;
  //   item_(active_index_).fill = palette_.fill(ItemStatus::Active);
  //   item_(active_index_).countur = palette_.countur(ItemStatus::Active);
  //   active_animator_.startAnimation(item_(active_index_));
  //   port_.notify();
  // }
}

void GraphGeomModel::onMouseMove_(const QPointF& position) {
  // assert(data_.has_value());
  // if (active_index_ != k_non) {
  //   item_(active_index_).center = position - diff_;
  //   port_.notify();
  // }
}

void GraphGeomModel::onMouseRelease_(const QPointF& position) {
  // assert(data_.has_value());
  // if (active_index_ == k_non)
  //   return;
  // active_animator_.stopAnimation();
  // diff_ = {0., 0.};
  // size_t index = std::exchange(active_index_, k_non);
  // int row = getRow_(position);
  // int column = getColumn_(position);
  // action_port_.set(std::in_place_t(), index, row, column);
}

void GraphGeomModel::onGraph(Graph& data) {
  if (!data_.has_value())
    data_.emplace();

  size_t countVertices = data.getVerticesCount();
  double xc = 400.;
  double yc = 300.;
  double R = 100;
  int i = 0;
  for (auto vertex : std::views::keys(data.AdjLists_)) {
    double angle = 2 * std::numbers::pi * i / countVertices;
    QPointF center = {xc + R * std::cos(angle), yc + R * std::sin(angle)};
    i += 1;
    data_->nodes.insert({vertex, DrawGraph::DrawNode{center, 10, Qt::black, vertex}});
  }

  for (const auto &[vertex, outEdges] : data.AdjLists_) {
    for (const auto &outEdge : outEdges) {
      data_->edges[vertex].push_back(DrawGraph::DrawEdge{vertex, outEdge.v, Qt::black});
    }
  }
}

int GraphGeomModel::touchedNode(const QPointF& position) const {
  assert(data_.has_value());

  for (const auto &drawNode : std::views::values(data_->nodes)) {
    QPointF diff = drawNode.center - position;
    if (std::sqrt(QPointF::dotProduct(diff, diff)) < drawNode.radius) {
      return drawNode.id;
    }
  }

  return -1;
}

} // namespace Kernel
} // namespace QApp

