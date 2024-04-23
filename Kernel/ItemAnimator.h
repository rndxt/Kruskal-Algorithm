#pragma once

#include "DrawData.h"

#include <QColor>
#include <QTimer>

#include <functional>

namespace QApp {
namespace Kernel {

class LabelAnimator : public QObject {
  Q_OBJECT

  using DrawLabelInfo = DrawData::DrawLabelInfo;
  using Action = std::function<void(const DrawLabelInfo&)>;

public:
  LabelAnimator(Action f);
  LabelAnimator(const LabelAnimator&) = delete;
  LabelAnimator(LabelAnimator&&) noexcept = delete;
  LabelAnimator& operator=(const LabelAnimator&) = delete;
  LabelAnimator& operator=(LabelAnimator&&) noexcept = delete;

  void startAnimation(const DrawLabelInfo&);

private Q_SLOTS:
  void onTimer();

private:
  Action action_;
  DrawLabelInfo current_;
  bool active_ = false;
  QTimer timer_;
};

} // namespace Kernel
} // namespace QApp
