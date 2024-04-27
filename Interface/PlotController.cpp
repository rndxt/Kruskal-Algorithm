#include "PlotController.h"

#include "Kernel/GeomModel.h"

#include <QDebug>

#include <cassert>

namespace QApp {
namespace Interface {

AlgorithmController::AlgorithmController(GeomModel* host)
    : host_(host),
      port_([this](MouseData&& data) { control(std::move(data)); }),
      button_port_(
          [this](ButtonData&& data) { controlButton(std::move(data)); }),
      slider_port_(
          [this](SliderData&& data) { controlSlider(std::move(data)); }),
      repr_port_([this](ModelData&& data) { controlRepr(std::move(data)); }) {
  assert(host_);
}

AlgorithmController::Observer* AlgorithmController::port() {
  return &port_;
}

AlgorithmController::ObserverButton* AlgorithmController::buttonPort() {
  return &button_port_;
}

AlgorithmController::ObserverSlider* AlgorithmController::sliderPort() {
  return &slider_port_;
}

AlgorithmController::ObserverModel* AlgorithmController::reprPort() {
  return &repr_port_;
}

void AlgorithmController::control(MouseData&& data) {
  if (data.has_value())
    controlOnData(*data);
}

void AlgorithmController::controlOnData(const MouseAction& action) {
  host_->handleMouseAction(action);
}

void AlgorithmController::controlButton(ButtonData&& data) {
  if (data.has_value())
    controlOnButtonData(*data);
}

void AlgorithmController::controlOnButtonData(const ButtonAction& action) {
  host_->handleButtonAction(action);
}

void AlgorithmController::controlSlider(SliderData&& data) {
  if (data.has_value())
    controlOnSliderData(*data);
}

void AlgorithmController::controlOnSliderData(int action) {
  host_->handleSliderAction(action);
}

void AlgorithmController::controlRepr(ModelData&& data) {
  if (data.has_value())
    controlOnReprData(*data);
}

void AlgorithmController::controlOnReprData(
    const std::vector<std::vector<int>>& action) {
  host_->handleReprAction(action);
}

} // namespace Interface
} // namespace QApp
