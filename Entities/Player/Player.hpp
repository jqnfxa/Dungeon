#pragma once
#include "../Interface/EntityInterface.hpp"

class Player : public EntityInterface {
 private:
  Position position_;

  int32_t health_;
  int32_t armor_;
  int32_t attack_;
  int32_t defence_;
  int32_t points_;

  static void adjust(int32_t &value, const int32_t &limit);
 public:
  Player(const Player &player);
  Player(Player &&player) noexcept;
  Player &operator=(const Player &player);
  Player &operator=(Player &&player) noexcept;

  explicit Player(const Position &position = Position(0, 0), const int32_t &health = 100, const int32_t &armor = 0, const int32_t &attack = 10, const int32_t &defence = 10, const int32_t &points = 0);

  [[nodiscard]] Position get_position() const override;
  [[nodiscard]] int32_t get_health() const override;
  [[nodiscard]] int32_t get_armor() const override;
  [[nodiscard]] int32_t get_attack() const override;
  [[nodiscard]] int32_t get_defense() const override;
  [[nodiscard]] int32_t get_points() const;

  void set_position(const Position &new_value) override;
  void set_health(const int32_t &new_value) override;
  void set_attack(const int32_t &new_value) override;
  void set_defense(const int32_t &new_value) override;
  void set_points(const int32_t &new_value);
};
