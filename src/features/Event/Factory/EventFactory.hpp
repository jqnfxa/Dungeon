#pragma once

#include "../Interface/EventInterface.hpp"
#include "../../Handlers/PlayerHandler/PlayerHandler.hpp"
#include <unordered_map>

enum EVENT_TYPE {
	SPIKES, POTION, SHIELD_KIT, STAR, RANDOM_MINE
};

class EventFactory {
 private:
  EventFactory();
  void clear_events();

  std::unordered_map<EVENT_TYPE, EventInterface *> events;
 public:
  EventFactory(EventFactory const &) = delete;
  EventFactory &operator=(EventFactory const &) = delete;
  ~EventFactory();

  static EventFactory &instance()
  {
	  static EventFactory instance_;
	  return instance_;
  }
  EventInterface *create(EVENT_TYPE type);
};
