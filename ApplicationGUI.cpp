#include "ApplicationGUI.h"

namespace QApp {

ApplicationGUI::MainWindow* ApplicationGUI::mainWindow() {
  return &main_window_;
}

ApplicationGUI::View* ApplicationGUI::view() {
  return main_window_.view();
}

} // namespace QApp
