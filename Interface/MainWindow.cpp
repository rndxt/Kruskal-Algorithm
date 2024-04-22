#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <qwt_plot.h>

namespace QApp {
namespace Interface {

MainWindow::MainWindow() : ui_(std::make_unique<Ui::MainWindow>()) {
  ui_->setupUi(this);
  QVBoxLayout* vboxLayout = new QVBoxLayout(ui_->centralwidget);

  QHBoxLayout* hboxLayout = new QHBoxLayout();
  QPushButton* editButton = new QPushButton("Edit graph");
  QPushButton* runButton = new QPushButton("Run");
  QSlider* slider = new QSlider(Qt::Orientation::Horizontal);
  QLabel* label = new QLabel("label");

  hboxLayout->addWidget(editButton, 0, Qt::AlignLeft);
  hboxLayout->addWidget(runButton, 1, Qt::AlignLeft);
  hboxLayout->addWidget(slider, 2, Qt::AlignLeft);
  hboxLayout->addWidget(label, 3, Qt::AlignRight);

  vboxLayout->addLayout(hboxLayout);
  vboxLayout->addWidget(view_.plot());
}

View* MainWindow::view() {
  return &view_;
}

MainWindow::~MainWindow() = default;

} // namespace Interface
} // namespace QApp
