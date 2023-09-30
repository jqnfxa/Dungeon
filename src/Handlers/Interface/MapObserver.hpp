#pragma once

#include "Movement/Aliases.hpp"
#include "Event/Interface/EventInterface.hpp"
#include "World/Cell.hpp"

class MapObserver {
 public:
  virtual ~MapObserver() = default;
  [[nodiscard]] virtual bool can_move(const Position &position) const = 0;
  [[nodiscard]] virtual Cell &get_cell(const Position &point) const = 0;
  [[nodiscard]] virtual std::vector<Position> find_route(const Position &begin, const Position &end) const = 0;
};