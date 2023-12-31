#pragma once
#include <cstdint>
#include "../Math/Vector2.hpp"
#include "../Movement/Aliases.hpp"
#include "Cell.hpp"

#define MAP_DIMENSION_UPPER_BOUND 1000
#define MAP_DIMENSION_LOWER_BOUND 10

class Map {
 private:
  Dimension dimensions_;
  Position start_;
  Position finish_;

  Cell **map_;

  void clear_map();
  Cell **allocate_map(const Dimension &dimensions);
 public:
  Map();
  Map(int32_t dim_x, int32_t dim_y);
  explicit Map(const Dimension &dimensions);

  Map(const Map &other);
  Map(Map &&other) noexcept;

  Map &operator=(const Map &other);
  Map &operator=(Map &&other) noexcept;

  void reset_start(const Position &point);
  void reset_finish(const Position &point);
  void build_wall(const Position &point);
  void destroy_wall(const Position &point);

  void set_cell(const Position &point, Cell &&new_cell);
  void set_cell(const Position &point, const Cell &new_cell);

  [[nodiscard]] const Position &get_start_point() const;
  [[nodiscard]] const Position &get_finish_point() const;
  [[nodiscard]] Cell &get_cell(const Position &point) const;
  [[nodiscard]] const Dimension &get_dimensions() const;
  [[nodiscard]] bool is_on_map(const Position &point) const;
  [[nodiscard]] bool is_adjacent_to_movable(const Position &point) const;

  ~Map();
};
