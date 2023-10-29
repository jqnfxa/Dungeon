#pragma once

#include <SFML/Window/Event.hpp>
#include "Command/Interface/Interface.hpp"

enum MENU_TEXTURE
{
	MAIN_MENU,
	PLAY_MENU,
	SETTINGS_MENU,
	WIN,
	LOSE
};

class RenderSlave {
 public:
  virtual ~RenderSlave() = default;
  virtual Command *on_key_press(const sf::Event &event) = 0;
  virtual void on_exit() = 0;
  virtual void render(const GameEngine &game) = 0;
};
