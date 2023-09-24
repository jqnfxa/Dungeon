#pragma once
#include "../Interface/HandlerInterface.hpp"
#include "World/Map.hpp"

class MapHandler : public HandlerInterface {
 private:
  Map *map_;
 public:
  MapHandler() = delete;
  explicit MapHandler(Map *map);
  ~MapHandler();

  [[nodiscard]] bool can_move(const Position &point) const;
  [[nodiscard]] Cell &get_cell(const Position &point) const;
  void set_cell(const Position &point, const Cell &new_cell) const;
  void set_cell(const Position &point, Cell &&new_cell) const;
};