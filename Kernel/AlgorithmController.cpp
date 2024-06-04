#include "AlgorithmController.h"

#include "AlgorithmModel.h"

#include <cassert>

namespace QApp {
namespace Kernel {

AlgorithmController::AlgorithmController(AlgorithmModel* model)
    : host_(model),
      port_([this](ItemData&& data) { onItemData(std::move(data)); }),
      model_port_(
          [this](ModelData&& data) { onNewModelData(std::move(data)); }) {
  assert(host_);
}

AlgorithmController::Observer* AlgorithmController::port() {
  return &port_;
}

void AlgorithmController::onItemData(ItemData&& data) {
  if (data.has_value())
    onItemAction(std::move(*data));
}

void AlgorithmController::onItemAction(ItemAction action) {
  assert(host_);
  host_->makeNextStep();
}

void AlgorithmController::onNewModelData(ModelData&& data) {
  if (data.has_value())
    onNewModelAction(std::move(*data));
}

void AlgorithmController::onNewModelAction(
    const std::vector<std::vector<int>>& action) {
  assert(host_);
  host_->replaceModel(action);
}

} // namespace Kernel
} // namespace QApp
