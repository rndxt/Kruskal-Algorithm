#include "AlgorithmModel.h"

#include <QDebug>
#include <cassert>

namespace QApp {
namespace Kernel {

AlgorithmModel::AlgorithmModel() : algorithm_(std::in_place_t()) {}

void AlgorithmModel::subscribe(ObserverAlgorithm* obs) {
  assert(obs);
  port_.subscribe(obs);
}

void AlgorithmModel::subscribeToNextStep(ObserverAlgorithm* obs) {
  assert(obs);
  next_step_port_.subscribe(obs);
}

void AlgorithmModel::makeNextStep() {
  if (!algorithm_.has_value())
    return;
  algorithm_->doNextStep();
  next_step_port_.notify();
}

} // namespace Kernel
} // namespace QApp
