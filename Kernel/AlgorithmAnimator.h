#pragma once

#include <QTimer>
#include <chrono>
#include <functional>

namespace QApp {
namespace Kernel {

class AlgorithmAnimator : public QObject {
  Q_OBJECT

  using milliseconds = std::chrono::milliseconds;
  using Action = std::function<void(void)>;

public:
  AlgorithmAnimator(Action f);
  AlgorithmAnimator(const AlgorithmAnimator&) = delete;
  AlgorithmAnimator(AlgorithmAnimator&&) noexcept = delete;
  AlgorithmAnimator& operator=(const AlgorithmAnimator&) = delete;
  AlgorithmAnimator& operator=(AlgorithmAnimator&&) noexcept = delete;

  void startAnimation();
  void setSpeed(int value);
  void pauseAnimation();

private Q_SLOTS:
  void onTimer();

private:
  static constexpr milliseconds defaultSpeed = milliseconds{1000};

  Action action_;
  milliseconds speed = defaultSpeed;
  bool active_ = false;
  bool done_ = false;
  QTimer timer_;
};

} // namespace Kernel
} // namespace QApp
