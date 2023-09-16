#pragma once
#include "../../Math/Vector2.hpp"
#include "../../Movement/Aliases.hpp"

class EntityInterface {
 public:
  virtual ~EntityInterface() = default;

  [[nodiscard]] virtual Position get_position() const = 0;
  [[nodiscard]] virtual int32_t get_health() const = 0;
  [[nodiscard]] virtual int32_t get_armor() const = 0;
  [[nodiscard]] virtual int32_t get_attack() const = 0;
  [[nodiscard]] virtual int32_t get_defense() const = 0;

  virtual void set_position(const Position &new_position) = 0;
  virtual void set_health(const int32_t &new_value) = 0;
  virtual void set_attack(const int32_t &new_value) = 0;
  virtual void set_defense(const int32_t &new_value) = 0;
};