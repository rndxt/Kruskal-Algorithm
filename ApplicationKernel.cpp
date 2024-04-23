#include "ApplicationKernel.h"

namespace QApp {

ApplicationKernel::ApplicationKernel()
    : algorithm_controller_(&model_) {
  model_.subscribe(geom_model_.port());
  model_.subscribeToNextStep(geom_model_.nextStepPort());
  geom_model_.subscribeToItemAction(algorithm_controller_.port());
  geom_model_.subscribeToItemAction(algorithm_controller_.port());
  geom_model_.new_model_port_.subscribe(&algorithm_controller_.model_port_);
}

} // namespace QApp
