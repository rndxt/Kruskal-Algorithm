#include "ApplicationKernel.h"

namespace QApp {

ApplicationKernel::ApplicationKernel()
    : field_controller_(&model_), field_controller2_(&model_) {
  model_.subscribe(geom_model_.port());
  model_.subscribe(geom_model2_.port());
  geom_model_.subscribeToItemAction(field_controller_.port());
  geom_model2_.subscribeToItemAction(field_controller2_.port());
}

} // namespace QApp
