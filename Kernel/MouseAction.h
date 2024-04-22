#pragma once

#include <QPointF>

namespace QApp {
namespace Kernel {

enum class EMouseStatus { Pressed, Moved, Released };

struct MouseAction {
  EMouseStatus status;
  QPointF position;
};

enum class EButtonStatus { RunAnimation, PauseAnimation };

struct ButtonAction {
  EButtonStatus status;
};

} // namespace Kernel
} // namespace QApp
