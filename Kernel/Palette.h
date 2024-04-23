#pragma once

#include "Algorithm.h"

#include <QColor>
#include <QPointF>
#include <array>

namespace QApp {
namespace Kernel {

enum class ItemStatus : int { Inactive, Active, END };

struct ItemStatusF {
  static constexpr int toIndex(ItemStatus status) {
    return static_cast<int>(status);
  }
  static constexpr int size() {
    return toIndex(ItemStatus::END);
  }
  static ItemStatus fromInt(int);
};

struct EdgeStatusF {
  static constexpr int toIndex(EdgeStatus status) {
    return static_cast<int>(status);
  }

  static constexpr int size() {
    return toIndex(EdgeStatus::Unknown) + 1;
  }
  static EdgeStatus fromInt(int);
};

struct Palette {
  double field_hight = 2.;
  double field_width = 3.;
  QPointF field_origin = {1., 2.};

  double node_radius = 10;

  QColor edgeCountur(EdgeStatus status) const;
  QColor nodeCountur(ItemStatus status) const;

private:
  std::array<QColor, 2> nodeCountur_ = {Qt::black, Qt::gray};
  std::array<QColor, EdgeStatusF::size()> edgeCountur_
      = {QColor("orange"), Qt::darkGray, Qt::black};
};

} // namespace Kernel
} // namespace QApp
