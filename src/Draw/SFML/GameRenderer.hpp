#pragma once

#include <SFML/Graphics.hpp>
#include <queue>
#include <vector>
#include "RenderSlave.hpp"
#include "Button.hpp"
#include "PlayerStatistic.hpp"

enum GAME_TEXTURE {
	PLAYER,
	START,
	FINISH,
	MOVABLE,
	WALL,
	DOOR,
	LOCK,
	KEY,
	RANDOM_MINE,
	SPIKES,
	POTION,
	SHIELD_KIT,
	STAR
};

class GameRenderer : public RenderSlave {
 public:
  sf::RenderWindow &parent_;
  sf::Font &font_;
  SfmlInput &binds_;
  PlayerStatistic statistic_;

  sf::Vector2f tile_size_;
  std::vector<sf::Texture> textures_;

  void destroy();
  void load_textures();
  std::queue<sf::Sprite> build_tile(const Cell &cell, const sf::Vector2f &position, bool can_move);
  void add_sprite(std::queue<sf::Sprite> &tile, const sf::Vector2f &position, GAME_TEXTURE texture);
 public:
  GameRenderer(sf::RenderWindow &parent, sf::Font &font, SfmlInput &binds);
  Command *on_key_press(const sf::Event &event) override;
  void on_exit() override;
  void render(const GameEngine &game) override;
};
