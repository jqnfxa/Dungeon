#pragma once
#include "../Interface/EntityInterface.hpp"

class Player : public EntityInterface {
 private:
  const int32_t health_lim_ = 200;
  const int32_t armor_lim_ = 100;
  const int32_t attack_lim_ = 50;
  const int32_t defence_lim_ = 50;
  const int32_t points_lim_ = 1000;

  Position position_;

  int32_t health_;
  int32_t armor_;
  int32_t attack_;
  int32_t defence_;
  int32_t points_;

  void adjust(int32_t &value, int32_t limit);
 public:
  Player(const Player &player);
  Player(Player &&player) noexcept;
  Player &operator=(const Player &player);
  Player &operator=(Player &&player) noexcept;

  explicit Player(const Position &position = Position(0, 0),
				  int32_t health = 100,
				  int32_t armor = 0,
				  int32_t attack = 10,
				  int32_t defence = 10,
				  int32_t points = 0);

  [[nodiscard]] Position get_position() const override;
  [[nodiscard]] int32_t get_health() const override;
  [[nodiscard]] int32_t get_armor() const override;
  [[nodiscard]] int32_t get_attack() const override;
  [[nodiscard]] int32_t get_defense() const override;
  [[nodiscard]] int32_t get_points() const;

  void set_position(const Position &new_value) override;
  void set_health(int32_t new_value) override;
  void set_armor(int32_t new_value) override;
  void set_attack(int32_t new_value) override;
  void set_defense(int32_t new_value) override;
  void set_points(int32_t new_value);
};
