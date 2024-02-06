#include "except.h"

#include <exception>
#include <iostream>

namespace NSProject {
void react() {
  try {
    throw;
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }
}
} // namespace NSProject
