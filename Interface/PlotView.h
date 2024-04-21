#pragma once

#include <QObject>

#include <memory>
#include <optional>

class QwtPlot;
class QwtPlotPicker;

namespace QApp {
namespace Interface {

class PlotView : public QObject {
  Q_OBJECT

public:
  PlotView();
  ~PlotView();

  QwtPlot* plot();

private:
  static void adjustPlot(QwtPlot*);
  void setPicker(QwtPlotPicker*);

  void drawData();
  void clear();
  void draw();

  std::unique_ptr<QwtPlot> plot_;
  QwtPlotPicker* picker_;
};

} // namespace Interface
} // namespace QApp
