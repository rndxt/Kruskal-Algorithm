#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#include <vector>

namespace NSProject {

class DisjointSet {
  using Container = std::vector<size_t>;

public:
  using Index = size_t;

  DisjointSet() = default;
  explicit DisjointSet(Index n);

  void join(Index lhs, Index rhs);
  Index find(Index elem) const; // maybe non const if do optimizations
  size_t getCountSets() const;

private:
  Container Sets_;
  size_t CountSets_;
};

} // namespace NSProject

#endif // DISJOINTSET_H