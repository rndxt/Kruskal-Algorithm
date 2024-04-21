#pragma once

#include "Kernel/DrawData.h"
#include "Kernel/MouseAction.h"
#include "QObserver.h"

#include <QObject>

#include <memory>
#include <optional>

class QwtPlot;
class QwtPlotPicker;

namespace QApp {
namespace Interface {

class View : public QObject {
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
  View();
  ~View();

  ObserverState* port();
  void subscribe(ObserverMouse* obs);

  QwtPlot* plot();

private Q_SLOTS:
  void mousePressed(const QPointF& pos);
  void mouseMoved(const QPointF& pos);
  void mouseReleased(const QPointF& pos);

private:
  static void adjustPlot(QwtPlot*);
  void setPicker(QwtPlotPicker*);

  void drawData(Data&& data);
  void clear();
  void draw(const DrawData& data);
  void addItem(const ItemOnField& item, const QPointF& field_origin);
  void drawField(const FieldData& field);
  static QVector<QPointF> makeVerticalPath(const FieldData& field);
  static QVector<QPointF> makeHorizontalPath(const FieldData& field);
  void addPathToPlot(const FieldData& field, QVector<QPointF>&& path);
  void drawVerticalLines(const FieldData& field);
  void drawHorizontalLines(const FieldData& field);

  std::unique_ptr<QwtPlot> plot_;
  QwtPlotPicker* picker_;
  ObserverState in_port_;
  ObservableMouse out_port_;
};

} // namespace Interface
} // namespace QApp
