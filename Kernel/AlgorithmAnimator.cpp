#include "AlgorithmAnimator.h"

#include <QDebug>
#include <cassert>

namespace QApp {
namespace Kernel {

AlgorithmAnimator::AlgorithmAnimator(Action f) : action_(std::move(f)) {
  assert(action_);
  QObject::connect(&timer_, &QTimer::timeout, this,
                   &AlgorithmAnimator::onTimer);
}

void AlgorithmAnimator::startAnimation() {
  active_ = true;
  timer_.start(speed);
}

void AlgorithmAnimator::setSpeed(int value) {
  if (active_)
    return;
  speed = defaultSpeed / value;
}

void AlgorithmAnimator::pauseAnimation() {
  active_ = false;
  timer_.stop();
}

void AlgorithmAnimator::onTimer() {
  action_();
}

} // namespace Kernel
} // namespace QApp
