#pragma once

#include "DrawData.h"

#include <QColor>
#include <QTimer>

#include <functional>

namespace QApp {
namespace Kernel {

class ItemAnimator : public QObject {
  Q_OBJECT
  using Item = DrawData::Item;
  using Action = std::function<void(const Item&)>;

public:
  ItemAnimator(Action f);
  ItemAnimator(const ItemAnimator&) = delete;
  ItemAnimator(ItemAnimator&&) noexcept = delete;
  ItemAnimator& operator=(const ItemAnimator&) = delete;
  ItemAnimator& operator=(ItemAnimator&&) noexcept = delete;

  void startAnimation(const Item&);
  void stopAnimation();

private Q_SLOTS:
  void onTimer();

private:
  double getNextRadius() const;
  QColor getNextColor() const;

  Action action_;
  Item current_;
  bool active_ = false;
  int step_ = 0;
  double initial_radius_ = 0.;
  QColor initial_color_;
  QTimer timer_;
};

} // namespace Kernel
} // namespace QApp
