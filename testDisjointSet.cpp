#include "testDisjointSet.h"

#include "DisjointSet.h"

#include <cassert>

namespace NSProject {

void NSTestsDSU::testCorrectInitialization() {
  size_t n = 10;
  DisjointSet DSU(n);
  assert(DSU.getCountSets() == n);
}

void NSTestsDSU::testFind() {
  size_t n = 15;
  DisjointSet DSU(n);

  bool isCorrect = true;
  for (size_t i = 0; i < n; ++i) {
    if (DSU.find(i) != i) {
      isCorrect = false;
      break;
    }
  }
  assert(isCorrect);
}

void NSTestsDSU::testJoin() {
  size_t n = 20;
  DisjointSet DSU(n);

  assert(DSU.find(0) != DSU.find(1));
  DSU.join(0, 1);
  assert(DSU.find(0) == DSU.find(1));

  for (size_t i = 2; i < n; ++i) {
    DSU.join(i, i - 1);
  }

  assert(DSU.getCountSets() == 1);
}

} // namespace NSProject