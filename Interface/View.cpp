#include "View.h"

#include <QPainterPath>
#include <QPen>
#include <QFont>
#include <qwt_picker_machine.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_picker.h>
#include <qwt_plot_shapeitem.h>
#include <qwt_plot_marker.h>
#include <qwt_text.h>
#include <QHeaderView>

#include <QDebug>

#include <cassert>

namespace QApp {
namespace Interface {

View::View()
    : plot_(std::make_unique<QwtPlot>()),
      vboxLayout_(std::make_unique<QVBoxLayout>()),
      hboxLayout_(std::make_unique<QHBoxLayout>()),
      editButton_(std::make_unique<QPushButton>("Edit graph")),
      runButton_(std::make_unique<QPushButton>("Run")),
      slider_(std::make_unique<QSlider>(Qt::Orientation::Horizontal)),
      label_(std::make_unique<QLabel>("label")),
      table_(std::make_unique<QTableWidget>()),
      picker_(new QwtPlotPicker(plot_->canvas())),
      in_port_([this](Data&& data) { drawData(std::move(data)); }) {
  assert(plot_);
  adjustPlot(plot_.get());
  setPicker(picker_);

  hboxLayout_->addWidget(editButton_.get(), 0, Qt::AlignLeft);
  QObject::connect(editButton_.get(), &QPushButton::clicked, this, &View::onEditButtonClicked);

  hboxLayout_->addWidget(runButton_.get(), 1, Qt::AlignLeft);
  QObject::connect(runButton_.get(), &QPushButton::clicked, this, &View::onRunButtonClicked);

  hboxLayout_->addWidget(slider_.get(), 2, Qt::AlignLeft);
  hboxLayout_->addWidget(label_.get(), 3, Qt::AlignRight);

  vboxLayout_->addLayout(hboxLayout_.get());
  vboxLayout_->addWidget(plot());

  table_->setEditTriggers(QAbstractItemView::NoEditTriggers);
  table_->horizontalHeader()->setVisible(false);
  table_->setRowCount(2);
  table_->setVerticalHeaderLabels({"Vertex", "index"});
  table_->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  vboxLayout_->addWidget(table_.get());
}

View::~View() = default;

View::ObserverState* View::port() {
  return &in_port_;
}

void View::subscribe(ObserverMouse* obs) {
  assert(obs);
  out_port_.subscribe(obs);
}

void View::subscribeRunButton(ObserverButton* obs) {
  assert(obs);
  out_button_port_.subscribe(obs);
}

QwtPlot* View::plot() {
  return plot_.get();
}

QVBoxLayout* View::layout() {
  return vboxLayout_.get();
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

void View::onRunButtonClicked() {
  qDebug() << "run button clicked";
  if (runButton_->text() == "Run") {
    runButton_->setText("Stop");
    out_button_port_.set(std::in_place_t(), EButtonStatus::RunAnimation);
  } else {
    assert(runButton_->text() == "Stop");
    runButton_->setText("Run");
    out_button_port_.set(std::in_place_t(), EButtonStatus::PauseAnimation);
  }
}

void View::onEditButtonClicked() {
  qDebug() << "edit button clicked";
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
  table_->setColumnCount(size(data.table));
  for (size_t column = 0; auto [vertex, up] : data.table) {
    table_->setItem(0, column, new QTableWidgetItem(QString::number(vertex)));
    table_->setItem(1, column, new QTableWidgetItem(QString::number(up)));
    column += 1;
  }
  table_->resizeColumnsToContents();

  plot_->detachItems();
  for (auto& [id, node]: data.nodes) {
    drawNode(node);
  }

  for (auto& [id, outEdges] : data.edges) {
    assert(std::ranges::is_sorted(outEdges, {}, &DrawEdge::vertexId));
    auto it = std::ranges::lower_bound(outEdges, id, {}, &DrawEdge::vertexId);
    auto v = std::ranges::subrange(it, end(outEdges));
    for (auto &outEdge : v) {
      assert(data.nodes.contains(id));
      assert(data.nodes.contains(outEdge.vertexId));
      drawEdge(data.nodes.find(outEdge.vertexId)->second,
               data.nodes.find(id)->second, outEdge);
    }
  }
  plot_->replot();
}

void View::drawNode(const DrawNode& node) {
  std::unique_ptr<QwtPlotShapeItem> plot_item =
      std::make_unique<QwtPlotShapeItem>();
  QPainterPath path;
  path.addEllipse(node.center, node.radius, node.radius);
  plot_item->setShape(path);
  plot_item->setPen(QPen(node.contur, 2));
  plot_item.release()->attach(plot_.get());

  std::unique_ptr<QwtPlotMarker> marker = std::make_unique<QwtPlotMarker>();
  marker->setValue(node.center);
  QwtText label = QwtText(QString::number(node.id));
  QFont font = label.font();
  font.setPixelSize(22);
  label.setFont(font);
  marker->setLabel(label);
  marker.release()->attach(plot_.get());
}

void View::drawEdge(const DrawNode& first, const DrawNode& second, const DrawEdge& outEdge) {
  QPointF v = second.center - first.center;
  v /= std::sqrt(QPointF::dotProduct(v, v));
  QPointF p1 = first.center + first.radius * v;
  QPointF p2 = second.center - second.radius * v;

  std::unique_ptr<QwtPlotShapeItem> plot_item =
      std::make_unique<QwtPlotShapeItem>();
  QPainterPath path;
  path.moveTo(p1);
  path.lineTo(p2);
  plot_item->setShape(path);
  plot_item->setPen(QPen(outEdge.contur, 3));
  plot_item.release()->attach(plot_.get());

  double partCoeff = 3;
  QPointF k = v;
  k.ry() *= -1.;
  k = k.transposed();
  k /= std::sqrt(QPointF::dotProduct(k, k));
  QPointF labelPos = (partCoeff * p1 + p2) / (1 + partCoeff) + 5 * k;

  std::unique_ptr<QwtPlotMarker> marker = std::make_unique<QwtPlotMarker>();
  marker->setValue(labelPos);
  QwtText label = QwtText(QString::number(outEdge.w));
  QFont font = label.font();
  font.setPixelSize(22);
  label.setFont(font);
  label.setColor(outEdge.contur);
  marker->setLabel(label);
  marker.release()->attach(plot_.get());
}

} // namespace Interface
} // namespace QApp
