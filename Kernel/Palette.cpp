#include "Palette.h"

#include <cassert>

namespace QApp {
namespace Kernel {

NodeStatus NodeStatusF::fromInt(int index) {
  assert(index < size() && index >= 0);
  return static_cast<NodeStatus>(index);
}

EdgeStatus EdgeStatusF::fromInt(int index) {
  assert(index < size() && index >= 0);
  return static_cast<EdgeStatus>(index);
}

QColor Palette::nodeCountur(NodeStatus status) const {
  return nodeCountur_[NodeStatusF::toIndex(status)];
}

QColor Palette::edgeCountur(EdgeStatus status) const {
  return edgeCountur_[EdgeStatusF::toIndex(status)];
}

} // namespace Kernel
} // namespace QApp
