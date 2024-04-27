#pragma once

#include "ApplicationGUI.h"
#include "ApplicationKernel.h"
#include "Interface/PlotController.h"

namespace QApp {

class ApplicationImpl : protected ApplicationKernel, protected ApplicationGUI {
  using PlotController = Interface::AlgorithmController;

public:
  ApplicationImpl();

private:
  PlotController controller_;
};

} // namespace QApp
