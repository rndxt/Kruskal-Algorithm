#include "FieldModel.h"

#include <QDebug>

#include <cassert>

namespace QApp {
namespace Kernel {

FieldModel::FieldModel() : field_(std::in_place_t()) {
}

void FieldModel::subscribe(ObserverField* obs) {
  assert(obs);
  port_.subscribe(obs);
}

void FieldModel::makeMove(const ItemAction& action) {
  port_.notify();
}

} // namespace Kernel
} // namespace QApp
