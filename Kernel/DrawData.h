#pragma once

#include <QColor>
#include <QPointF>

#include <array>
#include <vector>
#include <unordered_map>

namespace QApp {
namespace Kernel {

struct DrawData {
  struct DrawChangesOfTableItem {
    int vertex;
    int newIndex;
  };

  using DrawChangesTable = std::array<DrawChangesOfTableItem, 2>;

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
  std::unordered_map<int, int> table;
};

} // namespace Kernel
} // namespace QApp
