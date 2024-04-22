#include "ApplicationImpl.h"

#include <QDebug>

namespace QApp {

ApplicationImpl::ApplicationImpl()
    : controller_(&geom_model_) {
  geom_model_.subscribeToDrawData(view()->port());
  view()->subscribe(controller_.port());
  mainWindow()->show();
}

} // namespace QApp
