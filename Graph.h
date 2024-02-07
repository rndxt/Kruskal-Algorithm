#ifndef GRAPH_H
#define GRAPH_H

#include <set>
#include <vector>

namespace NSProject {

class Graph {
public:
  using Vertex = size_t;
  using Weight = size_t;
  using Pair = std::pair<Vertex, Weight>;

  struct Edge {
    Vertex u, v;
    Weight w;

    friend bool operator<(const Edge &lhs, const Edge &rhs) {
      return lhs.w < rhs.w;
    }
  };

  Graph() = default;
  explicit Graph(size_t V);

  void addEdge(Edge e);
  void removeEdge(Edge e);

  Graph getMST() const;

  size_t getCountVertex() const;
  size_t getCountEdges() const;

private:
  using AdjacentList = std::set<Pair>;
  using Container = std::vector<AdjacentList>;
  using EdgesList = std::multiset<Edge>;

  EdgesList getSortedEdges() const;
  AdjacentList &adjacent(Vertex u);
  const AdjacentList &adjacent(Vertex u) const;

  Container AdjLists_;
  size_t E_ = 0;
};

} // namespace NSProject

#endif // GRAPH_H
