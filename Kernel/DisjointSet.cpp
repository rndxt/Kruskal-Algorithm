#include "DisjointSet.h"

#include "DisjointSet.h"

#include <cassert>

namespace QApp {
namespace Kernel {

void DisjointSet::makeSet(DisjointSet::Element elem) {
  assert(Sets_.count(elem) == 0);
  Sets_.insert({elem, elem});
  CountSets_ += 1;
}

void DisjointSet::join(DisjointSet::Element lhs, DisjointSet::Element rhs) {
  Element represenLhs = findSet(lhs);
  Element represenRhs = findSet(rhs);
  Sets_[represenLhs] = represenRhs;
  assert(CountSets_ > 1);
  CountSets_ -= (represenLhs != represenRhs);
  assert(CountSets_ > 0);
}

DisjointSet::Element DisjointSet::findSet(DisjointSet::Element elem) const {
  assert(Sets_.count(elem) == 1);
  while (elem != getParent(elem)) {
    elem = getParent(getParent(elem));
  }
  return elem;
}

int DisjointSet::getCountSets() const {
  assert(CountSets_ > 0);
  return CountSets_;
}

DisjointSet::Element DisjointSet::getParent(DisjointSet::Element elem) const {
  assert(Sets_.count(elem) == 1);
  return Sets_.find(elem)->second;
}

} // namespace Kernel
} // namespace QApp
