#include "MainWindow.h"
#include "ui_MainWindow.h"

namespace QApp {
namespace Interface {

MainWindow::MainWindow() : ui_(std::make_unique<Ui::MainWindow>()) {
  ui_->setupUi(this);
  ui_->centralwidget->setLayout(view_.layout());
}

View* MainWindow::view() {
  return &view_;
}

MainWindow::~MainWindow() = default;

} // namespace Interface
} // namespace QApp
