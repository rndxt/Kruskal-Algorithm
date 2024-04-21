#pragma once

#include <random>

namespace QApp {
namespace Library {

class Random {
public:
  int uniformRGBValue();

private:
  std::mt19937_64 generator_{42};
};

} // namespace Library
} // namespace QApp
