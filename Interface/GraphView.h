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

class GraphView : public QObject {
  Q_OBJECT

  using DrawGraph = Kernel::DrawGraph;
  using Data = std::optional<DrawGraph>;
  using ObserverState = Library::CObserver<Data>;

  using EMouseStatus = Kernel::EMouseStatus;
  using MouseAction = Kernel::MouseAction;
  using MouseData = std::optional<MouseAction>;
  using ObservableMouse = Library::CObservableDataMono<MouseData>;
  using ObserverMouse = Library::CObserver<MouseData>;

public:
  GraphView();
  ~GraphView();

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
  void draw(const DrawGraph& g);
  void drawNode(const DrawGraph::DrawNode& node);
  void drawEdge(const DrawGraph::DrawEdge& edge);

  std::unique_ptr<QwtPlot> plot_;
  QwtPlotPicker* picker_;
  ObserverState in_port_;
  ObservableMouse out_port_;
};

} // namespace Interface
} // namespace QApp

