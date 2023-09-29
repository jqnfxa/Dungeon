#pragma once
#include <cstdint>
#include "World/GameField.hpp"

class Generator {
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
  std::vector<Position> find_route(GameField *map);
 public:
  Generator() = delete;
  Generator &operator=(const Generator &generator) = delete;
  Generator &operator=(Generator &&generator) = delete;
  Generator(int32_t m, int32_t n, int32_t total_percent, int32_t positive_events_percent, int32_t negative_events_percent, int32_t other_events_percent);
  void generate_maze(GameField *map);
  [[nodiscard]] GameField *generate();
};
