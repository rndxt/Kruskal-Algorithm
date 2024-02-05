#include "DisjointSet.h"

#include <cassert>
#include <iterator>
#include <numeric>

namespace NSProject {

DisjointSet::DisjointSet(Index n) : CountSets_(n), Sets_(n) {
  std::iota(Sets_.begin(), Sets_.end(), 0);
}

void DisjointSet::join(Index lhs, Index rhs) {
  assert(find(lhs) != find(rhs));
  Sets_[lhs] = Sets_[rhs];
  assert(CountSets_ > 1);
  CountSets_ -= 1;
  assert(CountSets_ > 0);
}

DisjointSet::Index DisjointSet::find(Index elem) const {
  while (elem != Sets_[elem]) {
    elem = Sets_[elem];
  }
  return elem;
}

size_t DisjointSet::getCountSets() const {
  assert(CountSets_ > 0);
  return CountSets_;
}

} // namespace NSProject