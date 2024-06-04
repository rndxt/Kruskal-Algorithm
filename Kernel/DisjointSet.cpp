#include "DisjointSet.h"

#include "DisjointSet.h"

#include <cassert>

namespace QApp {
namespace Kernel {

void DisjointSet::makeSet(Element elem) {
  assert(!Sets_.contains(elem));
  Sets_.insert({elem, elem});
  CountSets_ += 1;
}

void DisjointSet::join(Element lhs, Element rhs) {
  Element represenLhs = find(lhs);
  Element represenRhs = find(rhs);
  Sets_[represenLhs] = represenRhs;
  assert(CountSets_ > 1);
  CountSets_ -= (represenLhs != represenRhs);
  assert(CountSets_ > 0);
}

DisjointSet::Element DisjointSet::find(Element elem) const {
  assert(Sets_.contains(elem));
  while (elem != getParent(elem)) {
    elem = getParent(getParent(elem));
  }
  return elem;
}

int DisjointSet::getCountSets() const {
  assert(CountSets_ > 0);
  return CountSets_;
}

DisjointSet::Element DisjointSet::getParent(Element elem) const {
  assert(Sets_.contains(elem));
  return Sets_.find(elem)->second;
}

void DisjointSet::clear() {
  Sets_.clear();
}

} // namespace Kernel
} // namespace QApp
