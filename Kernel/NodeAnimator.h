#pragma once

#include "DrawData.h"

#include <QColor>
#include <QTimer>

#include <functional>

namespace QApp {
namespace Kernel {

class NodeAnimator : public QObject {
  Q_OBJECT

  using DrawNode = DrawData::DrawNode;
  using Action = std::function<void(const DrawNode&, const DrawNode&)>;

public:
  NodeAnimator(Action f);
  NodeAnimator(const NodeAnimator&) = delete;
  NodeAnimator(NodeAnimator&&) noexcept = delete;
  NodeAnimator& operator=(const NodeAnimator&) = delete;
  NodeAnimator& operator=(NodeAnimator&&) noexcept = delete;

  void startAnimation(const DrawNode&, const DrawNode&);

private Q_SLOTS:
  void onTimer();

private:
  using milliseconds = std::chrono::milliseconds;
  static constexpr milliseconds defaultTime = milliseconds{400};
  Action action_;
  DrawNode current_1;
  DrawNode current_2;
  QTimer timer_;
};

} // namespace Kernel
} // namespace QApp
