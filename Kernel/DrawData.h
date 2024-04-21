#pragma once

#include <QColor>
#include <QPointF>

#include <vector>
#include <unordered_map>

namespace QApp {
namespace Kernel {

struct DrawData {
  struct Field {
    int rows;
    int columns;
    double hight;
    double width;
  };
  struct FieldOnPlot : Field {
    QPointF origin;
  };
  struct Item {
    double radius;
    QColor fill;
    QColor countur;
  };

  struct ItemOnField : Item {
    QPointF center;
  };

  FieldOnPlot field;
  std::vector<ItemOnField> items;
};

struct DrawGraph {
  struct DrawNode {
    QPointF center;
    double radius;
    QColor contur;
    int id;
  };

  struct DrawEdge {
    int id1;
    int id2;
    QColor contur;
  };

  std::unordered_map<int, DrawNode> nodes;
  std::unordered_map<int, std::vector<DrawEdge>> edges;
};

} // namespace Kernel
} // namespace QApp
