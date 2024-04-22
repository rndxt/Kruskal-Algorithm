#pragma once

#include "DrawData.h"

#include "Graph.h"
#include "DisjointSet.h"

#include <QColor>
#include <QTimer>

#include <functional>

namespace QApp {
namespace Kernel {

class ItemAnimator : public QObject {
  Q_OBJECT

  using DrawEdge = DrawData::DrawEdge;
  using Action = std::function<void(int, const DrawEdge&)>;

public:
  ItemAnimator(Action f);
  ItemAnimator(const ItemAnimator&) = delete;
  ItemAnimator(ItemAnimator&&) noexcept = delete;
  ItemAnimator& operator=(const ItemAnimator&) = delete;
  ItemAnimator& operator=(ItemAnimator&&) noexcept = delete;

  void startAnimation(const Graph&);
  void stopAnimation();

private Q_SLOTS:
  void onTimer();

private:
  Action action_;
  Graph graph_;
  DrawEdge current_;
  DisjointSet dsu_;
  Graph::SortedEdges sortedEdges_;
  bool active_ = false;
  int step_ = 0;
  QTimer timer_;
};

} // namespace Kernel
} // namespace QApp
