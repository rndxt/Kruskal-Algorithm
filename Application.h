#pragma once

#include <memory>

namespace QApp {

class ApplicationImpl;

class Application {
public:
  Application();
  ~Application();

private:
  std::unique_ptr<ApplicationImpl> impl_;
};

} // namespace QApp
