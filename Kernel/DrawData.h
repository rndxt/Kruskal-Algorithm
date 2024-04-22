#pragma once

#include <QColor>
#include <QPointF>

#include <vector>
#include <unordered_map>

namespace QApp {
namespace Kernel {

struct DrawData {
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
};

} // namespace Kernel
} // namespace QApp
