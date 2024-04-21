#pragma once

#include "Kernel/DrawData.h"
#include "Kernel/MouseAction.h"
#include "QObserver.h"
#include "qtablewidget.h"

#include <QObject>

#include <memory>
#include <optional>

namespace QApp {
namespace Interface {

class TableView : public QObject {
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
  TableView();
  ~TableView();

  ObserverState* port();
  void subscribe(ObserverMouse* obs);

  QTableWidget* table();

private:
  // void drawData(Data&& data);
  // void clear();
  // void draw(const DrawData& data);

  ObserverState in_port_;
  ObservableMouse out_port_;
};

} // namespace Interface
} // namespace QApp
