#pragma once

#include "Kernel/MouseAction.h"
#include "QObserver.h"

#include <optional>

namespace QApp {
namespace Kernel {
class GeomModel;
}

namespace Interface {

class AlgorithmController {
  using GeomModel = Kernel::GeomModel;
  using EMouseStatus = Kernel::EMouseStatus;
  using MouseAction = Kernel::MouseAction;
  using MouseData = std::optional<MouseAction>;
  using Observer = Library::CObserver<MouseData>;

  using EButtonStatus = Kernel::EButtonStatus;
  using ButtonAction = Kernel::ButtonAction;
  using ButtonData = std::optional<ButtonAction>;
  using ObserverButton = Library::CObserver<ButtonData>;

  using SliderData = std::optional<int>;
  using ObservableSlider = Library::CObservableDataMono<SliderData>;
  using ObserverSlider = Library::CObserver<SliderData>;

  using ModelData = std::optional<std::vector<std::vector<int>>>;
  using ObservableModel = Library::CObservableDataMono<ModelData>;
  using ObserverModel = Library::CObserver<ModelData>;

public:
  AlgorithmController(GeomModel* host);

  Observer* port();
  ObserverButton* buttonPort();
  ObserverSlider* sliderPort();
  ObserverModel* reprPort();

private:
  void control(MouseData&& data);
  void controlOnData(const MouseAction& action);

  void controlButton(ButtonData&& data);
  void controlOnButtonData(const ButtonAction& action);

  void controlSlider(SliderData&& data);
  void controlOnSliderData(int action);

  void controlRepr(ModelData&& data);
  void controlOnReprData(const std::vector<std::vector<int>>& action);

  GeomModel* host_;
  Observer port_;
  ObserverButton button_port_;
  ObserverSlider slider_port_;
  ObserverModel repr_port_;
};

} // namespace Interface
} // namespace QApp
