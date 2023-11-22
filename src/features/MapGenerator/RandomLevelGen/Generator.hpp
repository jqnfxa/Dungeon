#pragma once

#include "World/GameField.hpp"
#include "Random/Random.hpp"
#include <cstdint>
#include <set>
#include <functional>

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

  void add_walls(GameField *map, const Position &position, std::vector<Wall> &walls);
  void generate_maze(GameField *map);

  [[nodiscard]] std::set<Position> get_all_movable_cells(GameField *map);
  [[nodiscard]] std::vector<EventInterface *> generate_events(int32_t lim, EVENT_GROUP group) const;
  [[nodiscard]] Position pick_random_empty_cell(std::set<Position> &movable_cells, std::function<bool(const Position &)> criteria);
  [[nodiscard]] std::vector<Position> invariant_route(std::set<Position> &movable_cells, GameField *map);

  void reset_points(std::set<Position> &movable_cells, GameField *map);
  void calculate_percentages(int32_t total_movable_cells);

  void add_additional_keys(std::set<Position> &movable_cells, GameField *map);
  void place_events(std::set<Position> &movable_cells, int32_t count, EVENT_GROUP group, GameField *map);
  void place_events_special(std::set<Position> &movable_cells, std::vector<Position> &route, int32_t count, EVENT_GROUP group, GameField *map);
 public:
  Generator() = delete;
  Generator &operator=(const Generator &generator) = delete;
  Generator &operator=(Generator &&generator) = delete;
  Generator(int32_t m, int32_t n, int32_t total_percent, int32_t positive_events_percent, int32_t negative_events_percent, int32_t other_events_percent);
  [[nodiscard]] GameField *generate();
};
