#include "GraphView.h"

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

GraphView::GraphView()
    : plot_(std::make_unique<QwtPlot>()),
      picker_(new QwtPlotPicker(plot_->canvas())),
      in_port_([this](Data&& data) { drawData(std::move(data)); }) {
  assert(plot_);
  adjustPlot(plot_.get());
  setPicker(picker_);
}

GraphView::~GraphView() = default;

GraphView::ObserverState* GraphView::port() {
  return &in_port_;
}

void GraphView::subscribe(ObserverMouse* obs) {
  assert(obs);
  out_port_.subscribe(obs);
}

QwtPlot* GraphView::plot() {
  return plot_.get();
}

void GraphView::mousePressed(const QPointF& pos) {
  out_port_.set(std::in_place_t(), EMouseStatus::Pressed, pos);
}

void GraphView::mouseMoved(const QPointF& pos) {
  out_port_.set(std::in_place_t(), EMouseStatus::Moved, pos);
}

void GraphView::mouseReleased(const QPointF& pos) {
  out_port_.set(std::in_place_t(), EMouseStatus::Released, pos);
}

void GraphView::adjustPlot(QwtPlot* plot) {
  plot->setAutoDelete(true);
  plot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  plot->setAxisVisible(QwtAxis::YLeft, false);
  plot->setAxisVisible(QwtAxis::XBottom, false);
}

void GraphView::setPicker(QwtPlotPicker* picker) {
  picker->setStateMachine(new QwtPickerDragPointMachine);
  QObject::connect(picker, &QwtPlotPicker::appended, this, &GraphView::mousePressed);
  QObject::connect(picker, &QwtPlotPicker::moved, this, &GraphView::mouseMoved);
  QObject::connect(picker, qOverload<const QPointF&>(&QwtPlotPicker::selected),
                   this, &GraphView::mouseReleased);
}

void GraphView::drawData(Data&& data) {
  if (data.has_value()) {
    draw(*data);
  } else {
    clear();
  }
}

void GraphView::clear() {
  plot_->detachItems();
  plot_->replot();
}

void GraphView::draw(const DrawGraph& g) {
  plot_->detachItems();
  for (auto& [id, node]: g.nodes) {
    drawNode(node);
  }

  for (auto& [id, outEdges] : g.edges) {
    for (auto &outEdge : outEdges) {
      drawEdge(outEdge);
    }
  }
  plot_->replot();
}

void GraphView::drawNode(const DrawGraph::DrawNode& node) {
  std::unique_ptr<QwtPlotShapeItem> plot_item =
      std::make_unique<QwtPlotShapeItem>();
  QPainterPath path;
  path.addEllipse(node.center, node.radius, node.radius);
  plot_item->setShape(path);
  plot_item->setPen(QPen(node.contur));
  plot_item.release()->attach(plot_.get());
}

void GraphView::drawEdge(const DrawGraph::DrawEdge& edge) {
}

} // namespace Interface
} // namespace QApp

