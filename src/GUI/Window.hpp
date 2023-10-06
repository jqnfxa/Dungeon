#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "Game/GameEngine.hpp"
#include "Command/Interface/Interface.hpp"
#include "GUI/Menus/Renderer.hpp"
#include "Menus/TILE_TYPES.hpp"

class Menu;

class Window {
  sf::Font font_;
  sf::Texture main_menu_texture_;
  sf::Texture play_menu_texture_;
  sf::Texture win_screen_texture_;
  sf::Texture death_screen_texture_;

  std::unordered_map<TILE_TYPE, sf::Texture> textures_;

  GameEngine &game_engine_;
  sf::RenderWindow window_;

  void load_textures();
  std::unordered_map<GameState::STATE, Renderer *> available_;
 public:
  Window(GameEngine &game, const sf::VideoMode &mode, const std::string &title, sf::Uint32 style = sf::Style::Default);
  ~Window();
  sf::RenderWindow &render_object();

  Command *process_input();
  void draw();
  GameState state() const;
};
