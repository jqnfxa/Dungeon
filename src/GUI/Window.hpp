#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "Game/GameEngine.hpp"
#include "Command/Interface/Interface.hpp"

class Menu;

class Window {
  sf::Font font_;
  sf::Texture main_menu_texture_;
  sf::Texture play_menu_texture_;

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
