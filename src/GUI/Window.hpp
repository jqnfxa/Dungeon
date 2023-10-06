#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "Menus/Interface/Menu.hpp"
#include "Game/GameEngine.hpp"
#include "Command/Interface/Interface.hpp"

class Window {
  GameEngine &game_engine_;
  sf::RenderWindow window_;

  std::unordered_map<GameState::STATE, Menu *> available_;
 public:
  Window(GameEngine &game, const sf::VideoMode &mode, const std::string &title, sf::Uint32 style = sf::Style::Default);
  ~Window();
  sf::RenderWindow &render_object();

  Command *process_input();
  void draw();
  GameState state() const;
};
