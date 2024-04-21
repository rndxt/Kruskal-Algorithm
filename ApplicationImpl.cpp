#include "ApplicationImpl.h"

namespace QApp {

ApplicationImpl::ApplicationImpl()
    : controller_(&geom_model_), controller2_(&geom_model2_) {
  geom_model_.subscribeToDrawData(view()->port());
  geom_model_.subscribeToDrawData(viewg()->port());
  geom_model2_.subscribeToDrawData(view2()->port());
  view()->subscribe(controller_.port());
  view2()->subscribe(controller2_.port());
  mainWindow()->show();
}

} // namespace QApp
