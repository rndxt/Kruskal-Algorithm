#include "NodeAnimator.h"

#include <QDebug>
#include <cassert>
#include <chrono>

namespace QApp {
namespace Kernel {

NodeAnimator::NodeAnimator(Action f) : action_(std::move(f)) {
  assert(action_);
  QObject::connect(&timer_, &QTimer::timeout, this, &NodeAnimator::onTimer);
}

void NodeAnimator::startAnimation(const DrawNode& node1,
                                  const DrawNode& node2) {
  current_1 = node1;
  current_1.contur = Qt::white;
  current_2 = node2;
  current_2.contur = Qt::white;
  action_(current_1, current_2);
  using namespace std::chrono;
  timer_.start(defaultTime);
}

void NodeAnimator::onTimer() {
  timer_.stop();
  current_1.contur = QColor("orange");
  current_2.contur = QColor("orange");
  action_(current_1, current_2);
}

} // namespace Kernel
} // namespace QApp
