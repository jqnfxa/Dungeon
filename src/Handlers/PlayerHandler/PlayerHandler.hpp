#pragma once
#include "../../Entities/Player/Player.hpp"
#include "../Interface/EntityHandler.hpp"
#include "../../Movement/Direction.hpp"
#include "../../World/GameField.hpp"
#include "Handlers/Interface/MapObserver.hpp"
#include "Event/MovementEvents/Key.hpp"

class PlayerHandler : public MapObserver, public EntityHandler {
 private:
  Player *player_;
  Position position_;
  MapSubject *map_observer_;
  std::vector<int64_t> keys_;
 public:
  ~PlayerHandler() override;
  PlayerHandler() = delete;
  explicit PlayerHandler(Player *player);

  void register_observer(MapSubject* observer) override;
  void remove_observer(MapSubject* observer) override;

  [[nodiscard]] const Position &get_position() const;
  [[nodiscard]] int32_t get_health() const;
  [[nodiscard]] int32_t get_armor() const;
  [[nodiscard]] int32_t get_attack() const;
  [[nodiscard]] int32_t get_defense() const;
  [[nodiscard]] int32_t get_points() const;
  [[nodiscard]] bool is_alive() const;
  [[nodiscard]] bool is_dead() const;
  [[nodiscard]] const std::vector<int64_t> &keys() const;

  void move_by_direction(DIRECTION direction, int32_t multiplier);
  void set_position(const Position &new_value);
  void set_health(int32_t new_value);
  void set_armor(int32_t new_value);
  void set_attack(int32_t new_value);
  void set_defense(int32_t new_value);
  void set_points(int32_t new_value);
  void add_key(int64_t key);
};
