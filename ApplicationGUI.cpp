#include "ApplicationGUI.h"

namespace QApp {

ApplicationGUI::MainWindow* ApplicationGUI::mainWindow() {
  return &main_window_;
}

ApplicationGUI::View* ApplicationGUI::view() {
  return main_window_.view();
}

ApplicationGUI::View* ApplicationGUI::viewg() {
  return main_window_.viewg();
}

ApplicationGUI::View* ApplicationGUI::view2() {
  return main_window_.view2();
}

} // namespace QApp
