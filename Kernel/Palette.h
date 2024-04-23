#pragma once

#include "EdgeStatus.h"

#include <QColor>
#include <QPointF>
#include <array>

namespace QApp {
namespace Kernel {

enum class NodeStatus : int { Inactive, Active, END };

struct NodeStatusF {
  static constexpr int toIndex(NodeStatus status) {
    return static_cast<int>(status);
  }
  static constexpr int size() {
    return toIndex(NodeStatus::END);
  }

  static NodeStatus fromInt(int);
};

struct Palette {
  double field_hight = 2.;
  double field_width = 3.;
  QPointF field_origin = {1., 2.};

  double node_radius = 10;

  QColor edgeCountur(EdgeStatus status) const;
  QColor nodeCountur(NodeStatus status) const;

private:
  std::array<QColor, 2> nodeCountur_ = {Qt::black, Qt::gray};
  std::array<QColor, EdgeStatusF::size()> edgeCountur_
      = {QColor("orange"), Qt::darkGray, Qt::black};
};

} // namespace Kernel
} // namespace QApp
