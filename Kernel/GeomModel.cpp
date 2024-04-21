#include "GeomModel.h"

#include <QDebug>

#include <cassert>
#include <ranges>

namespace QApp {
namespace Kernel {

GeomModel::GeomModel()
    : active_animator_([this](const Item& item) { onActiveAnimation_(item); }),
      in_port_([this](FieldData&& data) { onFieldData(std::move(data)); }) {
}

GeomModel::ObserverField* GeomModel::port() {
  return &in_port_;
}

void GeomModel::subscribeToDrawData(Observer* obs) {
  assert(obs);
  port_.subscribe(obs);
}

void GeomModel::subscribeToItemAction(ObserverAction* obs) {
  assert(obs);
  action_port_.subscribe(obs);
}

void GeomModel::handleMouseAction(const MouseAction& action) {
  if (!data_.has_value())
    return;
  QPointF local_position = action.position - field_().origin;
  switch (action.status) {
  case EMouseStatus::Pressed:
    onMousePress_(local_position);
    break;
  case EMouseStatus::Moved:
    onMouseMove_(local_position);
    break;
  case EMouseStatus::Released:
    onMouseRelease_(local_position);
    break;
  default:
    assert(false);
    break;
  }
}

void GeomModel::onMousePress_(const QPointF& position) {
  assert(data_.has_value());
  int index = touchedItem_(position);
  if (index != k_non) {
    active_index_ = index;
    diff_ = position - item_(active_index_).center;
    item_(active_index_).fill = palette_.fill(ItemStatus::Active);
    item_(active_index_).countur = palette_.countur(ItemStatus::Active);
    active_animator_.startAnimation(item_(active_index_));
    port_.notify();
  }
}

void GeomModel::onMouseMove_(const QPointF& position) {
  assert(data_.has_value());
  if (active_index_ != k_non) {
    item_(active_index_).center = position - diff_;
    port_.notify();
  }
}

void GeomModel::onMouseRelease_(const QPointF& position) {
  assert(data_.has_value());
  if (active_index_ == k_non)
    return;
  active_animator_.stopAnimation();
  diff_ = {0., 0.};
  size_t index = std::exchange(active_index_, k_non);
  int row = getRow_(position);
  int column = getColumn_(position);
  action_port_.set(std::in_place_t(), index, row, column);
}

void GeomModel::onActiveAnimation_(const Item& item) {
  assert(data_.has_value() && active_index_ != k_non);
  item_(active_index_).Item::operator=(item);
  port_.notify();
}

void GeomModel::onFieldData(FieldData&& data) {
  if (!data.has_value()) {
    if (data_.has_value()) {
      data_.reset();
      port_.notify();
    }
    return;
  }

  const Field& field = *data;
  if (!data_.has_value())
    data_.emplace();
  field_().rows = field.rows();
  field_().columns = field.columns();
  field_().hight = palette_.field_hight;
  field_().width = palette_.field_width;
  field_().origin = palette_.field_origin;

  data_->items.clear();
  data_->items.reserve(field.items().size());
  for (const auto& item : field.items()) {
    using ItemOnField = DrawData::ItemOnField;
    data_->items.emplace_back(
        ItemOnField{{.radius = palette_.item_radius,
                     .fill = palette_.fill(ItemStatus::Inactive),
                     .countur = palette_.countur(ItemStatus::Inactive)},
                    itemCenter_(item)});
  }
  port_.notify();
}

int GeomModel::getRow_(const QPointF& position) const {
  assert(data_.has_value());
  return std::floor(position.y() / field_().hight);
}

int GeomModel::getColumn_(const QPointF& position) const {
  return std::floor(position.x() / field_().width);
}

QPointF GeomModel::itemCenter_(const FieldItem& item) const {
  return {(0.5 + item.column()) * field_().width,
          (0.5 + item.row()) * field_().hight};
}

int GeomModel::touchedItem_(const QPointF& position) const {
  assert(data_.has_value());
  int index = data_->items.size() - 1;
  for (const auto& item : std::ranges::reverse_view(data_->items)) {
    QPointF diff = item.center - position;
    if (std::sqrt(QPointF::dotProduct(diff, diff)) < item.radius)
      return index;
    --index;
  }
  return k_non;
}

GeomModel::DrawField& GeomModel::field_() {
  assert(data_.has_value());
  return data_->field;
}

const GeomModel::DrawField& GeomModel::field_() const {
  assert(data_.has_value());
  return data_->field;
}

GeomModel::ItemOnField& GeomModel::item_(int index) {
  assert(data_.has_value());
  assert(size_t(index) < data_->items.size());
  assert(index >= 0);
  return data_->items[index];
}

const GeomModel::ItemOnField& GeomModel::item_(int index) const {
  assert(data_.has_value());
  assert(size_t(index) < data_->items.size());
  assert(index >= 0);
  return data_->items[index];
}

} // namespace Kernel
} // namespace QApp
