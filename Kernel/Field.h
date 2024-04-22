#pragma once

#include <cstdint>
#include <vector>

namespace QApp {
namespace Kernel {

enum class Direction { Up, Down, Left, Right };

class FieldItem {
public:
  FieldItem(int row, int column);

  int row() const;
  int column() const;

  void move(Direction direction);
  void moveTo(int row, int column);

private:
  int row_;
  int column_;
};

class Field {
  using FieldItems = std::vector<FieldItem>;

public:
  Fie();

  int rows() const;
  int columns() const;

  const FieldItems& items() const;
  const FieldItem& item(size_t index) const;
  void moveItem(size_t index, Direction direction);
  void moveItemTo(size_t index, int row, int column);

private:
  bool isAccessible(size_t index, int row, int column) const;
  static bool isVerticaleAdjacent(const FieldItem& item, int row, int column);
  static bool isHorizontalAdjacent(const FieldItem& item, int row, int column);

  static constexpr int k_default_rows = 5;
  static constexpr int k_default_columns = 7;

  int rows_ = k_default_rows;
  int columns_ = k_default_columns;
  FieldItems items_;
};

} // namespace Kernel
} // namespace QApp
