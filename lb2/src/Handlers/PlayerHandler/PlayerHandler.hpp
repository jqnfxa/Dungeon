#pragma once
#include "../../Entities/Player/Player.hpp"
#include "../../Movement/Direction.hpp"
#include "../../World/Map.hpp"
#include "../Interface/HandlerInterface.hpp"
#include "Handlers/MapHandler/MapHandler.hpp"

class PlayerHandler : public HandlerInterface {
 private:
  Player *player_;
  Position position_;
  MapHandler *map_handler_;
 public:
  ~PlayerHandler() override;
  PlayerHandler() = delete;
  explicit PlayerHandler(Player *player, MapHandler *handler = nullptr);
  MapHandler *reset_map_handler(MapHandler *handler);

  [[nodiscard]] const Position &get_position() const;
  [[nodiscard]] int32_t get_health() const;
  [[nodiscard]] int32_t get_armor() const;
  [[nodiscard]] int32_t get_attack() const;
  [[nodiscard]] int32_t get_defense() const;
  [[nodiscard]] int32_t get_points() const;

  void move_by_direction(DIRECTION direction, int32_t multiplier);
  void set_position(const Position &new_value);
  void set_health(int32_t new_value);
  void set_armor(int32_t new_value);
  void set_attack(int32_t new_value);
  void set_defense(int32_t new_value);
  void set_points(int32_t new_value);
};
