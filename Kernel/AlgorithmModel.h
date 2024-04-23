#pragma once

#include "Algorithm.h"
#include "QObserver.h"

#include <optional>

namespace QApp {
namespace Kernel {

class AlgorithmModel {
  using AlgorithmData = std::optional<Algorithm>;
  using ObservableAlgorithm = Library::CObservable<AlgorithmData>;
  using ObserverAlgorithm = Library::CObserver<AlgorithmData>;

public:
  AlgorithmModel();

  void subscribe(ObserverAlgorithm* obs);
  void subscribeToNextStep(ObserverAlgorithm* obs);
  void makeNextStep();

private:
  AlgorithmData algorithm_;
  ObservableAlgorithm port_
      = [this]() -> const AlgorithmData& { return algorithm_; };
  ObservableAlgorithm next_step_port_
      = [this]() -> const AlgorithmData& { return algorithm_; };
};

} // namespace Kernel
} // namespace QApp
