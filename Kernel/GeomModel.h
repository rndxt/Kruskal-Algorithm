#pragma once

#include "DrawData.h"
#include "Field.h"
#include "ItemAction.h"
#include "ItemAnimator.h"
#include "MouseAction.h"
#include "Palette.h"
#include "QObserver.h"

#include <optional>

namespace QApp {
namespace Kernel {

class GeomModel {

  using ItemOnField = DrawData::ItemOnField;
  using Item = DrawData::Item;
  using DrawField = DrawData::FieldOnPlot;

  using Data = std::optional<DrawData>;
  using Observable = Library::CObservable<Data>;
  using Observer = Library::CObserver<Data>;

  using FieldData = std::optional<Field>;
  using ObserverField = Library::CObserver<FieldData>;

  using ItemData = std::optional<ItemAction>;
  using ObservableAction = Library::CObservableDataMono<ItemData>;
  using ObserverAction = Library::CObserver<ItemData>;

public:
  GeomModel();

  ObserverField* port();
  void subscribeToDrawData(Observer* obs);
  void subscribeToItemAction(ObserverAction* obs);

  void handleMouseAction(const MouseAction& action);

private:
  void onMousePress_(const QPointF& position);
  void onMouseMove_(const QPointF& position);
  void onMouseRelease_(const QPointF& position);
  void onActiveAnimation_(const Item&);
  void onFieldData(FieldData&& data);

  int getRow_(const QPointF& position) const;
  int getColumn_(const QPointF& position) const;
  QPointF itemCenter_(const FieldItem&) const;
  int touchedItem_(const QPointF& position) const;

  DrawField& field_();
  const DrawField& field_() const;
  ItemOnField& item_(int index);
  const ItemOnField& item_(int index) const;

  static constexpr int k_non = -1;

  Data data_;
  Palette palette_;
  ItemAnimator active_animator_;
  int active_index_ = k_non;
  QPointF diff_ = {0., 0.};
  Observable port_ = [this]() -> const Data& { return data_; };
  ObserverField in_port_;
  ObservableAction action_port_;
};

} // namespace Kernel
} // namespace QApp
