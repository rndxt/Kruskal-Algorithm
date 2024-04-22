#pragma once

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

struct Palette {
  double field_hight = 2.;
  double field_width = 3.;
  QPointF field_origin = {1., 2.};

  double item_radius = 0.4 * std::min(field_hight, field_width);

  QColor fill(ItemStatus status) const;
  QColor countur(ItemStatus status) const;

private:
  std::array<QColor, ItemStatusF::size()> fill_ = {Qt::red, Qt::green};
  std::array<QColor, ItemStatusF::size()> countur_ = {Qt::black, Qt::gray};
};

} // namespace Kernel
} // namespace QApp
