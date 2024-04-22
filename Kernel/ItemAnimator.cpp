#include "ItemAnimator.h"

#include <QDebug>

#include <cassert>
#include <chrono>

namespace QApp {
namespace Kernel {

ItemAnimator::ItemAnimator(Action f) : action_(std::move(f)) {
  assert(action_);
  QObject::connect(&timer_, &QTimer::timeout, this, &ItemAnimator::onTimer);
}

void ItemAnimator::startAnimation(const Graph& graph) {
  graph_ = graph;
  active_ = true;
  step_ = 0;
  using namespace std::chrono;
  timer_.start(500ms);

  for (const auto &[u, outEdge] : graph_.AdjLists_) {
    dsu_.makeSet(u);
  }

  sortedEdges_ = graph_.getSortedEdges();
}

void ItemAnimator::stopAnimation() {
  active_ = false;
  timer_.stop();
  dsu_.clear();
  sortedEdges_.clear();
}

void ItemAnimator::onTimer() {
  if (active_ && step_ < graph_.getCountEdges()) {
    Graph::Edge e = sortedEdges_[step_];
    DrawEdge drawEdge = {e.v, e.w, QColorConstants::DarkGray};

    if (dsu_.findSet(e.u) != dsu_.findSet(e.v)) {
      dsu_.join(e.u, e.v);
      drawEdge.contur = QColor("orange");
    }
    action_(e.u, drawEdge);
    ++step_;
  }
}

} // namespace Kernel
} // namespace QApp
