#pragma once

#include "MapSubject.hpp"

class MapObserver {
 public:
  virtual ~MapObserver() = default;
  virtual void register_observer(MapSubject* observer) = 0;
  virtual void remove_observer(MapSubject* observer) = 0;
};