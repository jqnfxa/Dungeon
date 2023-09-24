#pragma once
#include <cstdint>
#include "World/Map.hpp"

class Generator {
  const int16_t random_tries_limit = 2;

  int32_t m_;
  int32_t n_;
  int32_t closed_cells;

  int32_t num_potions_;
  int32_t num_random_mines_;
  int32_t num_spikes_;

  [[nodiscard]] std::vector<EventInterface *> generate_events(int32_t lim) const;
 public:
  Generator() = delete;
  Generator &operator=(const Generator &generator) = delete;
  Generator &operator=(Generator &&generator) = delete;
  Generator(int32_t m, int32_t n, int32_t closed_cells_percent, int32_t total_events, int32_t positive_events_percent, int32_t negative_events_percent);
  [[nodiscard]] Map *generate() const;
};
