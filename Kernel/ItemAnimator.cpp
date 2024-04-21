#include "ItemAnimator.h"

#include "Library/Random.h"

#include <QDebug>

#include <cassert>
#include <chrono>
#include <numbers>

namespace QApp {
namespace Kernel {

namespace {
Library::Random& rand() {
  static Library::Random rnd;
  return rnd;
}

} // namespace

ItemAnimator::ItemAnimator(Action f) : action_(std::move(f)) {
  assert(action_);
  QObject::connect(&timer_, &QTimer::timeout, this, &ItemAnimator::onTimer);
}

void ItemAnimator::startAnimation(const Item& item) {
  current_ = item;
  active_ = true;
  step_ = 0;
  initial_radius_ = current_.radius;
  initial_color_ = current_.fill;
  using namespace std::chrono;
  timer_.start(40ms);
}

void ItemAnimator::stopAnimation() {
  active_ = false;
  timer_.stop();
}

void ItemAnimator::onTimer() {
  if (active_) {
    current_.radius += getNextRadius();
    current_.fill = getNextColor();
    action_(current_);
    ++step_;
  }
}

double ItemAnimator::getNextRadius() const {
  return 0.1 * initial_radius_ *
         std::sin((std::numbers::pi * step_) / (2. * 2));
}

QColor ItemAnimator::getNextColor() const {
  double r, g, b;
  initial_color_.getRgbF(&r, &g, &b);
  double dr = 0.0;
  double dg = 0.0;
  double db = 0.8;
  r += dr * (1. + sin((std::numbers::pi * step_) / (2. * 5))) / 2.;
  g += dg * (1. + sin((std::numbers::pi * step_) / (2. * 5))) / 2.;
  b += db * (1. + sin((std::numbers::pi * step_) / (2. * 5))) / 2.;
  r = std::min(std::max(r, 0.), 1.);
  g = std::min(std::max(g, 0.), 1.);
  b = std::min(std::max(b, 0.), 1.);
  return QColor::fromRgbF(r, g, b);
}

} // namespace Kernel
} // namespace QApp
