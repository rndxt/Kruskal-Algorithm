#include "MainWindow.h"
#include "ui_MainWindow.h"

namespace QApp {
namespace Interface {

MainWindow::MainWindow() : ui_(std::make_unique<Ui::MainWindow>()) {
  ui_->setupUi(this);

  QHBoxLayout* hboxLayout = new QHBoxLayout();
  hboxLayout->addWidget(view_.editButton(), 0, Qt::AlignLeft);
  hboxLayout->addWidget(view_.runButton(), 1, Qt::AlignLeft);
  hboxLayout->addWidget(view_.slider(), 2, Qt::AlignLeft);
  hboxLayout->addWidget(view_.label(), 3, Qt::AlignRight);

  QVBoxLayout* vboxLayout = new QVBoxLayout(ui_->centralwidget);
  vboxLayout->addLayout(hboxLayout);
  vboxLayout->addWidget(view_.plot());
  vboxLayout->addWidget(view_.table());
}

View* MainWindow::view() {
  return &view_;
}

MainWindow::~MainWindow() = default;

} // namespace Interface
} // namespace QApp
