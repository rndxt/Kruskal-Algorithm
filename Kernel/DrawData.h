#pragma once

#include <QColor>
#include <QPointF>
#include <array>
#include <unordered_map>
#include <vector>

namespace QApp {
namespace Kernel {

struct DrawData {
  struct DrawChangesOfTableItem {
    int vertex;
    int oldIndex;
  };

  using DrawLabelInfo = std::array<DrawChangesOfTableItem, 2>;

  struct DrawTableItem {
    int vertex;
    int index;
  };

  using DrawTable = std::vector<DrawTableItem>;

  struct DrawNode {
    QPointF center;
    double radius;
    QColor contur;
    int id;
  };

  struct DrawEdge {
    int vertexId;
    int w;
    QColor contur;
  };

  std::unordered_map<int, DrawNode> nodes;
  std::unordered_map<int, std::vector<DrawEdge>> edges;
  DrawTable table;
  DrawLabelInfo labelInfo;
};

} // namespace Kernel
} // namespace QApp
