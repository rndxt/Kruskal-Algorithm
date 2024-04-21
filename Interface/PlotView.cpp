#include "PlotView.h"

#include <QPainterPath>
#include <QPen>
#include <qwt_picker_machine.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_picker.h>
#include <qwt_plot_shapeitem.h>

#include <cassert>

namespace QApp {
namespace Interface {

namespace {

class SeriesQPointF : public QwtArraySeriesData<QPointF> {
public:
  SeriesQPointF(const QPointF& corner1, const QPointF& corner2)
      : rectangle_(corner1, corner2) {
  }
  QRectF boundingRect() const override {
    return rectangle_;
  }

private:
  QRectF rectangle_;
};

} // namespace

PlotView::PlotView()
    : plot_(std::make_unique<QwtPlot>()),
      picker_(new QwtPlotPicker(plot_->canvas())) {
  assert(plot_);
  adjustPlot(plot_.get());
  setPicker(picker_);
}

PlotView::~PlotView() = default;


QwtPlot* PlotView::plot() {
  return plot_.get();
}

void PlotView::adjustPlot(QwtPlot* plot) {
  plot->setAutoDelete(true);
  plot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  plot->setAxisVisible(QwtAxis::YLeft, false);
  plot->setAxisVisible(QwtAxis::XBottom, false);
}

void PlotView::setPicker(QwtPlotPicker* picker) {
}

void PlotView::drawData() {
}

void PlotView::clear() {
  plot_->detachItems();
  plot_->replot();
}

void PlotView::draw() {

}
} // namespace Interface
} // namespace QApp
