#include "Palette.h"

namespace QApp {
namespace Kernel {

QColor Palette::nodeCountur(NodeStatus status) const {
  return nodeCountur_[NodeStatusFuncs::toIndex(status)];
}

QColor Palette::edgeCountur(EdgeStatus status) const {
  return edgeCountur_[EdgeStatusFuncs::toIndex(status)];
}

} // namespace Kernel
} // namespace QApp
