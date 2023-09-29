#pragma once
#include <cstdint>
#include "../Math/Vector2.hpp"
#include "../Movement/Aliases.hpp"
#include "Cell.hpp"

#define MAP_DIMENSION_UPPER_BOUND 1000
#define MAP_DIMENSION_LOWER_BOUND 10

class GameField {
 private:
  Dimension dimensions_;
  Position start_;
  Position finish_;

  Cell **map_;

  void clear_map();
  Cell **allocate_map(const Dimension &dimensions);

  void swap_values(GameField &&other);
  void swap_values(const GameField &other);
 public:
  GameField();
  GameField(int32_t dim_x, int32_t dim_y);
  explicit GameField(const Dimension &dimensions);

  GameField(const GameField &other);
  GameField(GameField &&other) noexcept;

  GameField &operator=(const GameField &other);
  GameField &operator=(GameField &&other) noexcept;

  void reset_start(const Position &point);
  void reset_finish(const Position &point);
  void build_wall(const Position &point);
  void destroy_wall(const Position &point);

  void set_cell(const Position &point, Cell &&new_cell);
  void set_cell(const Position &point, const Cell &new_cell);

  [[nodiscard]] bool can_move(const Position &point) const;
  [[nodiscard]] const Position &start_point() const;
  [[nodiscard]] const Position &exit_point() const;
  [[nodiscard]] Cell &get_cell(const Position &point) const;
  [[nodiscard]] const Dimension &dimensions() const;
  [[nodiscard]] bool is_on_map(const Position &point) const;
  [[nodiscard]] bool is_adjacent_to_same_type(const Position &point) const;

  std::ostream &print(std::ostream &out) const;
  ~GameField();
};