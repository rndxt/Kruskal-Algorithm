#pragma once

#include "Kernel/MouseAction.h"
#include "QObserver.h"

#include <optional>

namespace QApp {
namespace Kernel {
class GeomModel;
}

namespace Interface {

class PlotController {
  using GeomModel = Kernel::GeomModel;
  using EMouseStatus = Kernel::EMouseStatus;
  using MouseAction = Kernel::MouseAction;
  using MouseData = std::optional<MouseAction>;
  using Observer = Library::CObserver<MouseData>;

  using EButtonStatus = Kernel::EButtonStatus;
  using ButtonAction = Kernel::ButtonAction;
  using ButtonData = std::optional<ButtonAction>;
  using ObserverButton = Library::CObserver<ButtonData>;

public:
  PlotController(GeomModel* host);

  Observer* port();
  ObserverButton* buttonPort();

private:
  void control(MouseData&& data);
  void controlOnData(const MouseAction& action);

  void controlButton(ButtonData&& data);
  void controlOnButtonData(const ButtonAction& action);

  GeomModel* host_;
  Observer port_;
  ObserverButton button_port_;
};

} // namespace Interface
} // namespace QApp
