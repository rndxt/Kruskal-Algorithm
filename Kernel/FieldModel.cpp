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
  qDebug() << "FieldModel::makeMove";
  // if (!field_.has_value())
  //   return;
  // field_->moveItemTo(action.index, action.row, action.column);
  port_.notify();
}

} // namespace Kernel
} // namespace QApp
