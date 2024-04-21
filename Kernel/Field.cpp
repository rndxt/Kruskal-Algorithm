#include "Field.h"

#include <cassert>

namespace QApp {
namespace Kernel {

FieldItem::FieldItem(int row, int column) : row_(row), column_(column) {
}

int FieldItem::row() const {
  return row_;
}

int FieldItem::column() const {
  return column_;
}

void FieldItem::move(Direction direction) {
  switch (direction) {
  case Direction::Up:
    ++row_;
    break;
  case Direction::Down:
    --row_;
    break;
  case Direction::Left:
    --column_;
    break;
  case Direction::Right:
    ++column_;
    break;
  default:
    assert(false);
    break;
  }
}

void FieldItem::moveTo(int row, int column) {
  row_ = row;
  column_ = column;
}

Field::Field() {
  items_.reserve(2);
  items_.emplace_back(0, 0);
  items_.emplace_back(1, 1);
}

int Field::rows() const {
  return rows_;
}

int Field::columns() const {
  return columns_;
}

const Field::FieldItems& Field::items() const {
  return items_;
}

const FieldItem& Field::item(size_t index) const {
  assert(index < items_.size());
  return items_[index];
}

void Field::moveItem(size_t index, Direction direction) {
  if (index >= items_.size())
    return;
  switch (direction) {
  case Direction::Up:
    if (items_[index].row() >= rows_)
      return;
  case Direction::Down:
    if (items_[index].row() <= 0)
      return;
    break;
  case Direction::Left:
    if (items_[index].column() <= 0)
      return;
    break;
  case Direction::Right:
    if (items_[index].column() >= columns_)
      return;
    break;
  default:
    assert(false);
    break;
  }
  items_[index].move(direction);
}

void Field::moveItemTo(size_t index, int row, int column) {
  if (index >= items_.size())
    return;
  if (!isAccessible(index, row, column))
    return;
  items_[index].moveTo(row, column);
}

bool Field::isAccessible(size_t index, int row, int column) const {
  assert(index < items_.size());
  if (row < 0 || row >= rows_ || column < 0 || column >= columns_)
    return false;
  return isVerticaleAdjacent(items_[index], row, column) ||
         isHorizontalAdjacent(items_[index], row, column);
}

bool Field::isVerticaleAdjacent(const FieldItem& item, int row, int column) {
  return (item.row() == row + 1 || item.row() == row - 1) &&
         item.column() == column;
}

bool Field::isHorizontalAdjacent(const FieldItem& item, int row, int column) {
  return (item.column() == column + 1 || item.column() == column - 1) &&
         item.row() == row;
}

} // namespace Kernel
} // namespace QApp
