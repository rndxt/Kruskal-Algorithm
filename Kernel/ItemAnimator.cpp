#include "ItemAnimator.h"

#include <QDebug>

#include <cassert>
#include <chrono>

namespace QApp {
namespace Kernel {

LabelAnimator::LabelAnimator(Action f) : action_(std::move(f)) {
  assert(action_);
  QObject::connect(&timer_, &QTimer::timeout, this, &LabelAnimator::onTimer);
}

void LabelAnimator::startAnimation(const DrawLabelInfo& info) {
  action_(info);
  active_ = true;
  using namespace std::chrono;
  timer_.start(200ms);
}

void LabelAnimator::onTimer() {
  timer_.stop();
}

} // namespace Kernel
} // namespace QApp
