#include "Application.h"

#include "ApplicationImpl.h"

namespace QApp {

Application::Application() : impl_(std::make_unique<ApplicationImpl>()) {
}

Application::~Application() = default;

} // namespace QApp
