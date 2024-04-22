#pragma once

#include "Graph.h"
#include "ItemAction.h"
#include "QObserver.h"

#include <optional>

namespace QApp {
namespace Kernel {

class FieldModel {
  using FieldData = std::optional<Graph>;
  using ObservableField = Library::CObservable<FieldData>;
  using ObserverField = Library::CObserver<FieldData>;

public:
  FieldModel();

  void subscribe(ObserverField* obs);
  void makeMove(const ItemAction& action);

private:
  FieldData field_;
  ObservableField port_ = [this]() -> const FieldData& { return field_; };
};

} // namespace Kernel
} // namespace QApp
