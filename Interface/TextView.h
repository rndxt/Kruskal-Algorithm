#pragma once

#include "Kernel/DrawData.h"
#include "Kernel/MouseAction.h"
#include "QObserver.h"

#include <QObject>
#include <QLabel>

#include <memory>
#include <optional>

namespace QApp {
namespace Interface {

class TextView : public QObject {
  Q_OBJECT
  using DrawData = Kernel::DrawData;
  using ItemOnField = DrawData::ItemOnField;

  using FieldData = DrawData::FieldOnPlot;
  using Data = std::optional<DrawData>;
  using ObserverState = Library::CObserver<Data>;

  using EMouseStatus = Kernel::EMouseStatus;
  using MouseAction = Kernel::MouseAction;
  using MouseData = std::optional<MouseAction>;
  using ObservableMouse = Library::CObservableDataMono<MouseData>;
  using ObserverMouse = Library::CObserver<MouseData>;

public:
  TextView();
  ~TextView();

  ObserverState* port();
  void subscribe(ObserverMouse* obs);

  QLabel* text();

private:

  ObserverState in_port_;
  ObservableMouse out_port_;
};

} // namespace Interface
} // namespace QApp
