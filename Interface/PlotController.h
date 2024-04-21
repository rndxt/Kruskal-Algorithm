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

public:
  PlotController(GeomModel* host);

  Observer* port();

private:
  void control(MouseData&& data);
  void controlOnData(const MouseAction& action);

  GeomModel* host_;
  Observer port_;
};

} // namespace Interface
} // namespace QApp
