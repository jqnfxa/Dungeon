#pragma once

#include "MapObserver.hpp"

class Subject {
 public:
  virtual ~Subject() = default;
  virtual void register_observer(MapObserver* observer) = 0;
  virtual void remove_observer(MapObserver* observer) = 0;
};