#pragma once

#include "View.h"

#include <QMainWindow>

#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace QApp {
namespace Interface {

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow();
  ~MainWindow();

  View* view();
  View* viewg();
  View* view2();

private:
  std::unique_ptr<Ui::MainWindow> ui_;
  View view_;
  View viewg_;
  View view2_;
};
} // namespace Interface
} // namespace QApp
