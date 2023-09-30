#pragma once

#include "World/GameField.hpp"
#include <cstdint>
#include <set>

class Generator {
 private:
  struct Wall {
	  Position pos;
	  Position cell1;
	  Position cell2;
  };

  int32_t m_;
  int32_t n_;

  const int32_t negative_default = 50;
  const int32_t positive_default = 30;
  const int32_t other_default = 20;

  int32_t total_percent;
  int32_t num_positive_;
  int32_t num_negative_;
  int32_t num_other_;

  [[nodiscard]] std::vector<EventInterface *> generate_events(int32_t lim, std::vector<int> events_count) const;
  void generate_maze(GameField *map);
  Position pick_random_empty_cell(std::set<Position> &movable_cells, std::function<bool(const Position &)> criteria);
  std::set<Position> get_all_movable_cells(GameField *map);
  void reset_points(std::set<Position> &movable_cells, GameField *map);
  void calculate_percentages(int32_t total_movable_cells);
  void place_spikes_on_route(std::set<Position> &movable_cells, GameField *map, int32_t at_most = 4);
  void add_walls(GameField *map, const Position &position, std::vector<Wall> &walls);
 public:
  Generator() = delete;
  Generator &operator=(const Generator &generator) = delete;
  Generator &operator=(Generator &&generator) = delete;
  Generator(int32_t m, int32_t n, int32_t total_percent, int32_t positive_events_percent, int32_t negative_events_percent, int32_t other_events_percent);
  [[nodiscard]] GameField *generate();
};
