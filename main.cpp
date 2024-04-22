#include "Application.h"
#include "Except.h"
#include "QRunTime.h"

int main(int argc, char* argv[]) {
  QApp::QRunTime runtime(argc, argv);
  try {
    QApp::Application app;
    runtime.exec();
  } catch (...) {
    QApp::Except::react();
  }
  return 0;
}
