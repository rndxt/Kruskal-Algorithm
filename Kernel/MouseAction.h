#pragma once

#include <QPointF>

namespace QApp {
namespace Kernel {

enum class EMouseStatus { Pressed, Moved, Released };

struct MouseAction {
  EMouseStatus status;
  QPointF position;
};

} // namespace Kernel
} // namespace QApp
