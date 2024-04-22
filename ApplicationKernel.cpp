#include "ApplicationKernel.h"

namespace QApp {

ApplicationKernel::ApplicationKernel()
    : field_controller_(&model_) {
  model_.subscribe(geom_model_.port());
  geom_model_.subscribeToItemAction(field_controller_.port());
}

} // namespace QApp
