#include "Palette.h"

#include <cassert>

namespace QApp {
namespace Kernel {

ItemStatus ItemStatusF::fromInt(int index) {
  assert(index < size() && index >= 0);
  if (index < 0 || index >= size())
    return ItemStatus::END;
  return static_cast<ItemStatus>(index);
}

QColor Palette::fill(ItemStatus status) const {
  return fill_[ItemStatusF::toIndex(status)];
}

QColor Palette::countur(ItemStatus status) const {
  return countur_[ItemStatusF::toIndex(status)];
}

} // namespace Kernel
} // namespace QApp
