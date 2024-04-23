#pragma once

#include "Kernel/AlgorithmController.h"
#include "Kernel/AlgorithmModel.h"
#include "Kernel/GeomModel.h"

namespace QApp {

class ApplicationKernel {
  using AlgorithmModel = Kernel::AlgorithmModel;
  using GeomModel = Kernel::GeomModel;
  using AlgorithmController = Kernel::AlgorithmController;

public:
  ApplicationKernel();

protected:
  AlgorithmModel model_;
  GeomModel geom_model_;
  AlgorithmController algorithm_controller_;
};

} // namespace QApp
