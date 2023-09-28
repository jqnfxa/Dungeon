#pragma once
#include <cstdint>
#include "World/Map.hpp"

class Generator {
  int32_t m_;
  int32_t n_;

  int32_t num_positive_;
  int32_t num_negative_;
  int32_t num_other_;

  [[nodiscard]] std::vector<EventInterface *> generate_events(int32_t lim) const;
  std::vector<Position> find_route(Map *map);
 public:
  Generator() = delete;
  Generator &operator=(const Generator &generator) = delete;
  Generator &operator=(Generator &&generator) = delete;
  Generator(int32_t m, int32_t n, int32_t total_events, int32_t positive_events_percent, int32_t negative_events_percent, int32_t other_events_percent);
  void generate_maze(Map *map);
  [[nodiscard]] Map *generate();
};
