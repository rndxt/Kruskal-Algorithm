#include "QTimeAnchor.h"

#include <QDebug>

namespace QApp {
namespace Library {

QTimeAnchor::QTimeAnchor(const char* msg) : msg_(msg) {
}

QTimeAnchor::~QTimeAnchor() {
  if (isActive_)
    stop();
}

void QTimeAnchor::stop() {
  double elapsed = timer_.get().toMicroSecondsF();
  qDebug() << msg_.c_str() << elapsed << "mc";
  isActive_ = false;
}

void QTimeAnchor::restart(const char* msg) {
  msg_ = msg;
  isActive_ = true;
  timer_.restart();
}

} // namespace Library
} // namespace QApp
