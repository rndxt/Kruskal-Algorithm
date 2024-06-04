#include "Random.h"

namespace QApp {
namespace Library {

int Random::uniformRGBValue() {
  std::uniform_int_distribution uni(0, 255);
  return uni(generator_);
}

} // namespace Library
} // namespace QApp
