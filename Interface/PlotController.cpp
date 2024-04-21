#include "PlotController.h"

#include "Kernel/GeomModel.h"

#include <QDebug>

#include <cassert>

namespace QApp {
namespace Interface {

PlotController::PlotController(GeomModel* host)
    : host_(host),
      port_([this](MouseData&& data) { control(std::move(data)); }) {
  assert(host_);
}

PlotController::Observer* PlotController::port() {
  return &port_;
}

void PlotController::control(MouseData&& data) {
  if (data.has_value())
    controlOnData(*data);
}

void PlotController::controlOnData(const MouseAction& action) {
  host_->handleMouseAction(action);
}

} // namespace Interface
} // namespace QApp
