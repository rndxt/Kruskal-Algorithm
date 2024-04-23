#pragma once

#include "Kernel/AlgorithmController.h"
#include "Kernel/AlgorithmModel.h"
#include "Kernel/GeomModel.h"

namespace QApp {

class ApplicationKernel {
  using AlgorithmModel = Kernel::AlgorithmModel;
  using GeomModel = Kernel::GeomModel;
  using FieldController = Kernel::FieldController;

public:
  ApplicationKernel();

protected:
  AlgorithmModel model_;
  GeomModel geom_model_;
  FieldController field_controller_;
};

} // namespace QApp
