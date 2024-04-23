#include "ApplicationImpl.h"

#include <QDebug>

namespace QApp {

ApplicationImpl::ApplicationImpl()
    : controller_(&geom_model_) {
  geom_model_.subscribeToDrawData(view()->port());
  view()->subscribe(controller_.port());
  view()->subscribeRunButton(controller_.buttonPort());
  view()->subscribeSlider(controller_.sliderPort());
  mainWindow()->show();
}

} // namespace QApp
