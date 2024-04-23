#pragma once

#include <array>
#include <cstdint>

namespace QApp {
namespace Kernel {

struct ItemAction {
  size_t index;
  int row;
  int column;
};

} // namespace Kernel
} // namespace QApp
