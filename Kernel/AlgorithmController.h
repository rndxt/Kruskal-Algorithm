#pragma once

#include "AlgorithmAction.h"
#include "QObserver.h"

#include <optional>

namespace QApp {
namespace Kernel {

class AlgorithmModel;

class AlgorithmController {
  using ItemData = std::optional<ItemAction>;
  using Observer = Library::CObserver<ItemData>;

  using ModelData = std::optional<std::vector<std::vector<int>>>;
  using ObservableModel = Library::CObservableDataMono<ModelData>;
  using ObserverModel = Library::CObserver<ModelData>;

public:
  AlgorithmController(AlgorithmModel* model);
  Observer* port();

  void onItemData(ItemData&& data);
  void onItemAction(ItemAction action);

  void onNewModelData(ModelData&& data);
  void onNewModelAction(const std::vector<std::vector<int>>& action);

  AlgorithmModel* host_;
  Observer port_;
  ObserverModel model_port_;
};

} // namespace Kernel
} // namespace QApp
