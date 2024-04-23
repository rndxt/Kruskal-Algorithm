#include "Palette.h"

#include <cassert>

namespace QApp {
namespace Kernel {

EdgeStatus EdgeStatusF::fromInt(int index) {
  assert(index < size() && index >= 0);
  return static_cast<EdgeStatus>(index);
}

// QColor Palette::fill(EdgeStatus status) const {
//   return fill_[EdgeStatusF::toIndex(status)];
// }

QColor Palette::nodeCountur(ItemStatus status) const {
  return nodeCountur_[ItemStatusF::toIndex(status)];
}

QColor Palette::edgeCountur(EdgeStatus status) const {
  return edgeCountur_[EdgeStatusF::toIndex(status)];
}

} // namespace Kernel
} // namespace QApp
