#pragma once

#include <unordered_map>

namespace QApp {
namespace Kernel {

class DisjointSet {
public:
  using Element = int;

  DisjointSet() = default;

  void makeSet(Element elem);
  void join(Element lhs, Element rhs);
  Element find(Element elem) const;
  int getCountSets() const;
  void clear();

private:
  using Container = std::unordered_map<Element, Element>;

  Element getParent(Element elem) const;

  Container Sets_;
  int CountSets_ = 0;
};

} // namespace Kernel
} // namespace QApp
