#include "PlotController.h"

#include "Kernel/GeomModel.h"

#include <QDebug>

#include <cassert>

namespace QApp {
namespace Interface {

PlotController::PlotController(GeomModel* host)
    : host_(host),
      port_([this](MouseData&& data) { control(std::move(data)); }),
      button_port_([this](ButtonData&& data) { controlButton(std::move(data)); }){
  assert(host_);
}

PlotController::Observer* PlotController::port() {
  return &port_;
}

PlotController::ObserverButton* PlotController::buttonPort() {
  return &button_port_;
}

void PlotController::control(MouseData&& data) {
  if (data.has_value())
    controlOnData(*data);
}

void PlotController::controlOnData(const MouseAction& action) {
  host_->handleMouseAction(action);
}

void PlotController::controlButton(ButtonData&& data) {
  if (data.has_value())
    controlOnButtonData(*data);
}

void PlotController::controlOnButtonData(const ButtonAction& action) {
  host_->handleButtonAction(action);
}

} // namespace Interface
} // namespace QApp
