#pragma once

namespace QApp {
namespace Kernel {

enum class EdgeStatus : int { InMst, NotInMst, Unknown };

namespace EdgeStatusFuncs {

static constexpr int toIndex(EdgeStatus status) {
  return static_cast<int>(status);
}

static constexpr int size() {
  return toIndex(EdgeStatus::Unknown) + 1;
}

}; // namespace EdgeStatusFuncs

} // namespace Kernel
} // namespace QApp
