#pragma once
#include <cstdint>

class Bot {
 private:
  uint32_t row_;
  uint32_t column_;

  uint32_t health_;
  uint32_t damage_;
  uint32_t armor_;
 public:
  Bot();
  Bot(uint32_t health, uint32_t damage, uint32_t armor);
  [[nodiscard]] bool is_alive() const;
  [[nodiscard]] uint32_t get_health() const;
  [[nodiscard]] uint32_t get_armor() const;
  [[nodiscard]] uint32_t get_damage() const;
  [[nodiscard]] uint32_t get_row() const;
  [[nodiscard]] uint32_t get_column() const;
  void set_column(uint32_t column);
  void set_row(uint32_t row);
  void set_health(uint32_t health);
  void set_armor(uint32_t armor);
  void set_damage(uint32_t damage);
};
