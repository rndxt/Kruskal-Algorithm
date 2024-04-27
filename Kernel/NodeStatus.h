#pragma once

namespace QApp {
namespace Kernel {

enum class NodeStatus : int { Inactive, Active, END };

namespace NodeStatusFuncs {

static constexpr int toIndex(NodeStatus status) {
  return static_cast<int>(status);
}

static constexpr int size() {
  return toIndex(NodeStatus::END);
}

}; // namespace NodeStatusFuncs

} // namespace Kernel
} // namespace QApp
