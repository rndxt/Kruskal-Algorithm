#pragma once

#include "Time.h"

#include <string>

namespace QApp {
namespace Library {

class QTimeAnchor {
public:
  QTimeAnchor(const char* msg);
  ~QTimeAnchor();
  void stop();
  void restart(const char*);

private:
  Timer timer_;
  std::string msg_;
  bool isActive_ = true;
};
} // namespace Library
} // namespace QApp
