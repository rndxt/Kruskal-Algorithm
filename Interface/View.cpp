#include "View.h"

#include <QDebug>
#include <QFont>
#include <QHeaderView>
#include <QInputDialog>
#include <QPainterPath>
#include <QPen>
#include <cassert>
#include <qwt_picker_machine.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_picker.h>
#include <qwt_plot_shapeitem.h>
#include <qwt_text.h>
#include <ranges>

namespace QApp {
namespace Interface {

View::View()
    : plot_(std::make_unique<QwtPlot>()),
      editButton_(std::make_unique<QPushButton>("Edit graph")),
      runButton_(std::make_unique<QPushButton>("Run")),
      slider_(std::make_unique<QSlider>(Qt::Orientation::Horizontal)),
      table_(std::make_unique<QTableWidget>()),
      picker_(new QwtPlotPicker(plot_->canvas())),
      in_port_([this](Data&& data) { drawData(std::move(data)); }) {
  assert(plot_);
  adjustPlot(plot_.get());
  setPicker(picker_);
  adjustTable(table_.get());

  QObject::connect(editButton_.get(), &QPushButton::clicked, this, &View::onEditButtonClicked);
  QObject::connect(runButton_.get(), &QPushButton::clicked, this, &View::onRunButtonClicked);
  QObject::connect(slider_.get(), &QSlider::valueChanged, this,
                   &View::onSliderValueChanged);

  slider_.get()->setMinimum(1);
  slider_.get()->setMaximum(4);
  slider_.get()->setTickInterval(1);
  slider_.get()->setTickPosition(QSlider::TicksBelow);
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

void View::subscribeSlider(ObserverSlider* obs) {
  assert(obs);
  slider_port_.subscribe(obs);
}

void View::subscribeNewModel(ObserverRepres* obs) {
  assert(obs);
  repr_port_.subscribe(obs);
}

QwtPlot* View::plot() {
  return plot_.get();
}

QPushButton* View::editButton() {
  return editButton_.get();
}

QPushButton* View::runButton() {
  return runButton_.get();
}

QSlider* View::slider() {
  return slider_.get();
}

QTableWidget* View::table() {
  return table_.get();
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
  qDebug() << runButton_->text() << " button clicked";
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
  runButton_->setText("Run");
  out_button_port_.set(std::in_place_t(), EButtonStatus::PauseAnimation);
  bool ok;
  QString text;
  ValidationResult res;
  do {
    text = QInputDialog::getMultiLineText(
        plot_.get(), "Edit graph",
        "Enter graph in Adjacency List notation, start with zero:", "", &ok);
    if (!ok)
      return;

  } while (text.isEmpty() || !(res = isUserInputValid(text), res.has_value()));
  repr_port_.set(std::in_place_t(), *res);
}

View::ValidationResult View::isUserInputValid(const QString& userInput) {
  auto lines = userInput.split(u'\n', Qt::SkipEmptyParts);
  auto firstLine = lines[0].split(u' ', Qt::SkipEmptyParts);
  std::vector<std::vector<int>> result;
  result.resize(lines.size());
  result[0].reserve(2);
  if (firstLine.size() != 2)
    return {};

  for (auto& part : firstLine) {
    if (!part.contains(QRegExp("[1-9][0-9]*"))) {
      return {};
    }
    result[0].push_back(part.toInt());
  }

  for (int i = 1; i < lines.size(); ++i) {
    result[i].reserve(3);
    auto parts = lines[i].split(u' ');

    if (parts.size() != 3) {
      return {};
    }

    for (auto& part : parts) {
      if (!part.contains(QRegExp("0|[1-9][0-9]*"))) {
        return {};
      }
      result[i].push_back(part.toInt());
    }
  }
  return result;
}

void View::onSliderValueChanged(int value) {
  qDebug() << "slider changed";
  slider_port_.set(std::in_place_t(), value);
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

void View::adjustTable(QTableWidget* table) {
  table->setEditTriggers(QAbstractItemView::NoEditTriggers);
  table->horizontalHeader()->setVisible(false);
  table->setRowCount(2);
  table->setVerticalHeaderLabels({"Vertex", "index"});
  table->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
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
  drawTable(data.table);

  plot_->detachItems();
  std::ranges::for_each(std::views::values(data.nodes),
                        [this](const DrawNode& node) { drawNode(node); });

  for (auto& [id, outEdges] : data.edges) {
    assert(std::ranges::is_sorted(outEdges, {}, &DrawEdge::vertexId));
    // all edges before already have been drawn
    auto it = std::ranges::lower_bound(outEdges, id, {}, &DrawEdge::vertexId);
    auto v = std::ranges::subrange(it, end(outEdges));
    for (auto& outEdge : v) {
      assert(data.nodes.contains(id));
      assert(data.nodes.contains(outEdge.vertexId));
      drawEdge(data.nodes.find(outEdge.vertexId)->second,
               data.nodes.find(id)->second, outEdge);
    }
  }
  plot_->replot();
}

void View::drawTable(const DrawTable& table) {
  table_->setColumnCount(size(table));
  for (size_t column = 0; auto [vertex, up] : table) {
    table_->setItem(0, column, new QTableWidgetItem(QString::number(vertex)));
    table_->setItem(1, column, new QTableWidgetItem(QString::number(up)));
    column += 1;
  }
  table_->resizeColumnsToContents();
}

void View::drawNode(const DrawNode& node) {
  std::unique_ptr<QwtPlotShapeItem> plot_item =
      std::make_unique<QwtPlotShapeItem>();
  QPainterPath path;
  path.addEllipse(node.center, node.radius, node.radius);
  plot_item->setShape(path);
  plot_item->setPen(QPen(node.contur, 2));
  if (node.contur == Qt::white)
    plot_item->setBrush(QBrush(QColor("orange")));
  plot_item.release()->attach(plot_.get());

  std::unique_ptr<QwtPlotMarker> marker = std::make_unique<QwtPlotMarker>();
  marker->setValue(node.center);
  QwtText label = QwtText(QString::number(node.id));
  if (node.contur == Qt::white)
    label.setColor(Qt::white);
  QFont font = label.font();
  font.setPixelSize(22);
  label.setFont(font);
  marker->setLabel(label);
  marker.release()->attach(plot_.get());
}

void View::drawEdge(const DrawNode& first, const DrawNode& second,
                    const DrawEdge& outEdge) {
  QPointF v = second.center - first.center;
  v /= std::sqrt(QPointF::dotProduct(v, v));
  QPointF p1 = first.center + first.radius * v;
  QPointF p2 = second.center - second.radius * v;

  std::unique_ptr<QwtPlotShapeItem> plot_item
      = std::make_unique<QwtPlotShapeItem>();
  QPainterPath path;
  path.moveTo(p1);
  path.lineTo(p2);
  plot_item->setShape(path);
  plot_item->setPen(QPen(outEdge.contur, 3));
  plot_item.release()->attach(plot_.get());

  constexpr double partCoeff = 3.;
  constexpr double resizeCoeff = 5.;
  QPointF k = {-v.y(), v.x()};
  k /= std::sqrt(QPointF::dotProduct(k, k));
  QPointF labelPos = (partCoeff * p1 + p2) / (1 + partCoeff) + resizeCoeff * k;

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
