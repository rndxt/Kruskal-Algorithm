#include "except.h"
#include "test.h"

int main() {
  try {
    NSProject::runAllTests();
  } catch (...) {
    NSProject::react();
  }
  return 0;
}
