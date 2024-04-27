#pragma once

#include "EdgeStatus.h"
#include "NodeStatus.h"

#include <QColor>
#include <QPointF>
#include <array>

namespace QApp {
namespace Kernel {

struct Palette {
  QPointF plot_center = {400., 300.};
  double radius = 100.;
  double field_width = 3.;
  QPointF field_origin = {1., 2.};

  double node_radius = 10;

  QColor edgeCountur(EdgeStatus status) const;
  QColor nodeCountur(NodeStatus status) const;

private:
  std::array<QColor, NodeStatusFuncs::size()> nodeCountur_
      = {Qt::black, Qt::gray};
  std::array<QColor, EdgeStatusFuncs::size()> edgeCountur_
      = {QColor("orange"), Qt::darkGray, Qt::black};
};

} // namespace Kernel
} // namespace QApp
