#pragma once

#include "../Interface/EventInterface.hpp"
#include "../../Handlers/PlayerHandler/PlayerHandler.hpp"

enum EVENT_TYPE {
	RANDOM_MINE, SPIKES, POTION, SHIELD_KIT, STAR
};

class EventFactory {
 private:
  EventFactory();

  PlayerHandler *handler_;
 public:
  EventFactory(EventFactory const &) = delete;
  EventFactory &operator=(EventFactory const &) = delete;
  static EventFactory &instance()
  {
	  static EventFactory instance_;
	  return instance_;
  }
  void reset_player_reference(PlayerHandler *handler);
  EventInterface *create(EVENT_TYPE type);
};