#pragma once

namespace QApp {
namespace Kernel {

enum class NodeStatus : int { Inactive, Active };

namespace NodeStatusFuncs {

static constexpr int toIndex(NodeStatus status) {
  return static_cast<int>(status);
}

static constexpr int size() {
  return toIndex(NodeStatus::Active) + 1;
}

}; // namespace NodeStatusFuncs

} // namespace Kernel
} // namespace QApp
