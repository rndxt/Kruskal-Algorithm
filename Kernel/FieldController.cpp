#include "FieldController.h"

#include "FieldModel.h"

#include <cassert>

namespace QApp {
namespace Kernel {

FieldController::FieldController(FieldModel* model)
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
  host_->makeMove(action);
}

} // namespace Kernel
} // namespace QApp
