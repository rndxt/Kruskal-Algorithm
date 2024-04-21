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

View::View()
    : plot_(std::make_unique<QwtPlot>()),
      picker_(new QwtPlotPicker(plot_->canvas())),
      in_port_([this](Data&& data) { drawData(std::move(data)); }) {
  assert(plot_);
  adjustPlot(plot_.get());
  setPicker(picker_);
}

View::~View() = default;

View::ObserverState* View::port() {
  return &in_port_;
}

void View::subscribe(ObserverMouse* obs) {
  assert(obs);
  out_port_.subscribe(obs);
}

QwtPlot* View::plot() {
  return plot_.get();
}

void View::mousePressed(const QPointF& pos) {
  out_port_.set(std::in_place_t(), EMouseStatus::Pressed, pos);
}

void View::mouseMoved(const QPointF& pos) {
  out_port_.set(std::in_place_t(), EMouseStatus::Moved, pos);
}

void View::mouseReleased(const QPointF& pos) {
  out_port_.set(std::in_place_t(), EMouseStatus::Released, pos);
}

void View::adjustPlot(QwtPlot* plot) {
  plot->setAutoDelete(true);
  plot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  plot->setAxisVisible(QwtAxis::YLeft, false);
  plot->setAxisVisible(QwtAxis::XBottom, false);
}

void View::setPicker(QwtPlotPicker* picker) {
  picker->setStateMachine(new QwtPickerDragPointMachine);
  QObject::connect(picker, &QwtPlotPicker::appended, this, &View::mousePressed);
  QObject::connect(picker, &QwtPlotPicker::moved, this, &View::mouseMoved);
  QObject::connect(picker, qOverload<const QPointF&>(&QwtPlotPicker::selected),
                   this, &View::mouseReleased);
}

void View::drawData(Data&& data) {
  if (data.has_value()) {
    draw(*data);
  } else {
    clear();
  }
}

void View::clear() {
  plot_->detachItems();
  plot_->replot();
}

void View::draw(const DrawData& data) {
  plot_->detachItems();
  drawField(data.field);
  for (const auto& item : data.items)
    addItem(item, data.field.origin);
  plot_->replot();
}

void View::addItem(const ItemOnField& item, const QPointF& field_origin) {
  std::unique_ptr<QwtPlotShapeItem> plot_item =
      std::make_unique<QwtPlotShapeItem>();
  QPainterPath path;
  path.addEllipse(item.center + field_origin, item.radius, item.radius);
  plot_item->setShape(path);
  plot_item->setPen(QPen(item.countur));
  plot_item->setBrush(QBrush(item.fill));
  plot_item.release()->attach(plot_.get());
}

void View::drawField(const FieldData& field) {
  plot_->setAxisScale(QwtAxis::YLeft, field.origin.y() - field.hight,
                      field.origin.y() + (field.rows + 1) * field.hight, 1);
  plot_->setAxisScale(QwtAxis::XBottom, field.origin.x() - field.width,
                      field.origin.x() + (field.columns + 1) * field.width, 1);
  drawVerticalLines(field);
  drawHorizontalLines(field);
}

QVector<QPointF> View::makeVerticalPath(const FieldData& field) {
  QPointF point = field.origin;
  QPointF vertical = QPointF(0., field.rows * field.hight);
  QPointF horizontal = QPointF(field.width, 0.);
  QVector<QPointF> path;
  path.push_back(point);
  for (int index = 0; index < field.columns; ++index) {
    point += vertical;
    path.push_back(point);
    point += horizontal;
    path.push_back(point);
    vertical *= -1;
  }
  point += vertical;
  path.push_back(point);
  return path;
}

QVector<QPointF> View::makeHorizontalPath(const FieldData& field) {
  QPointF point = field.origin;
  QPointF vertical = QPointF(0., field.hight);
  QPointF horizontal = QPointF(field.columns * field.width, 0.);
  QVector<QPointF> path;
  path.push_back(point);
  for (int index = 0; index < field.rows; ++index) {
    point += horizontal;
    path.push_back(point);
    point += vertical;
    path.push_back(point);
    horizontal *= -1;
  }
  point += horizontal;
  path.push_back(point);
  return path;
}

void View::addPathToPlot(const FieldData& field, QVector<QPointF>&& path) {
  std::unique_ptr<QwtPlotCurve> curve = std::make_unique<QwtPlotCurve>();
  QPointF origin = field.origin;
  QPointF corner = origin;
  corner += QPointF(field.columns * field.width, field.rows * field.hight);
  std::unique_ptr<SeriesQPointF> points =
      std::make_unique<SeriesQPointF>(origin, corner);
  points->setSamples(path);
  curve->setSamples(points.release());
  curve.release()->attach(plot_.get());
}

void View::drawVerticalLines(const FieldData& field) {
  QVector<QPointF> path = makeVerticalPath(field);
  addPathToPlot(field, std::move(path));
}

void View::drawHorizontalLines(const FieldData& field) {
  QVector<QPointF> path = makeHorizontalPath(field);
  addPathToPlot(field, std::move(path));
}
} // namespace Interface
} // namespace QApp
