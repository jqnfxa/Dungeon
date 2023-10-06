#pragma once

#include <queue>
#include "Menu.hpp"
#include "../Window.hpp"
#include "TILE_TYPES.hpp"


class GameFieldDrawer : public Renderer {
  sf::RenderWindow &render_window_;
  GameEngine &game_engine_;
  std::unordered_map<TILE_TYPE, sf::Texture> textures_;
  std::vector<std::vector<std::queue<sf::Sprite>>> render_map_;

  sf::Font font_;
  std::vector<sf::Text> stats_;
  std::vector<sf::Text> stats_values_;

  sf::Vector2f tile_size_;
  void add_text_field(std::vector<sf::Text> &stats, const sf::Font &font, const std::string &str, int32_t size, const sf::Color &color, const sf::Vector2f &position);
  void add_sprite(std::queue<sf::Sprite> &tile, const sf::Vector2f &position, const sf::Texture &texture);
  void build_tile(std::queue<sf::Sprite> &tile, const sf::Vector2f &position, const Cell &cell, bool can_move);
 public:
  explicit GameFieldDrawer(sf::RenderWindow &parent, GameEngine &game, const std::unordered_map<TILE_TYPE, sf::Texture> &textures);
  ~GameFieldDrawer() override;
  Command *on_key_press(const sf::Event &event) override;
  void draw() override;
};
