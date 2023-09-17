#pragma once
#include "../../Entities/Player/Player.hpp"
#include "../../Movement/Direction.hpp"

class PlayerHandler {
 private:
  Player *player_;
 public:
  ~PlayerHandler();
  PlayerHandler() = delete;
  explicit PlayerHandler(Player *player);

  [[nodiscard]] Position get_position() const;
  [[nodiscard]] int32_t get_health() const;
  [[nodiscard]] int32_t get_armor() const;
  [[nodiscard]] int32_t get_attack() const;
  [[nodiscard]] int32_t get_defense() const;
  [[nodiscard]] int32_t get_points() const;

  void move_by_direction(DIRECTION direction, int32_t multiplier);
  void set_position(const Position &new_value);
  void set_health(int32_t new_value);
  void set_attack(int32_t new_value);
  void set_defense(int32_t new_value);
  void set_points(int32_t new_value);
};
