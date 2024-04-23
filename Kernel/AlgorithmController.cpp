#include "AlgorithmController.h"

#include "AlgorithmModel.h"

#include <cassert>

namespace QApp {
namespace Kernel {

FieldController::FieldController(AlgorithmModel* model)
    : host_(model),
      port_([this](ItemData&& data) { onItemData(std::move(data)); }) {
  assert(host_);
}

FieldController::Observer* FieldController::port() {
  return &port_;
}

void FieldController::onItemData(ItemData&& data) {
  if (data.has_value())
    onItemAction(std::move(*data));
}

void FieldController::onItemAction(ItemAction action) {
  assert(host_);
  host_->makeNextStep();
}

} // namespace Kernel
} // namespace QApp
