#pragma once

#include "Kernel/FieldController.h"
#include "Kernel/FieldModel.h"
#include "Kernel/GeomModel.h"

namespace QApp {

class ApplicationKernel {
  using FieldModel = Kernel::FieldModel;
  using GeomModel = Kernel::GeomModel;
  using FieldController = Kernel::FieldController;

public:
  ApplicationKernel();

protected:
  FieldModel model_;
  GeomModel geom_model_;
  GeomModel geom_model2_;
  FieldController field_controller_;
  FieldController field_controller2_;
};

} // namespace QApp
