#pragma once

#include "AlgorithmAction.h"
#include "QObserver.h"

#include <optional>

namespace QApp {
namespace Kernel {

class AlgorithmModel;

class FieldController {
  using ItemData = std::optional<ItemAction>;
  using Observer = Library::CObserver<ItemData>;

public:
  FieldController(AlgorithmModel* model);
  Observer* port();

private:
  void onItemData(ItemData&& data);
  void onItemAction(ItemAction action);

  AlgorithmModel* host_;
  Observer port_;
};

} // namespace Kernel
} // namespace QApp
