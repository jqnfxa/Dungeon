#pragma once

#include "Movement/Aliases.hpp"
#include "Event/Interface/EventInterface.hpp"
#include "World/Cell.hpp"
#include <vector>

class MapSubject {
 public:
  virtual ~MapSubject() = default;
  [[nodiscard]] virtual bool can_move(EntityHandler *caller, const Position &position) const = 0;
  [[nodiscard]] virtual Cell &get_cell(const Position &point) const = 0;
  [[nodiscard]] virtual std::vector<Position> find_route(EntityHandler *caller, const Position &begin, const Position &end) const = 0;
};