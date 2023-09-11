#pragma once
#include <cstdint>
#include "Bot.hpp"

class Player : public Bot {
 private:
  uint32_t points_;
 public:
  Player();
  Player(uint32_t health, uint32_t points, uint32_t damage, uint32_t armor);
  [[nodiscard]] uint32_t get_points() const;
  void set_points(uint32_t points);
};
