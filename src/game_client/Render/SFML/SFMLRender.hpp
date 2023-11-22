#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "../IRender.hpp"
#include "World/Cell.hpp"


class SFMLRender : public IRender
{
	sf::RenderWindow &window_;
	sf::Font font_;

	sf::Vector2f tile_size_;

	sf::Texture load_texture(const std::string &full_path);
  	void load_textures();
  	std::queue<sf::Sprite> build_tile(const Cell &cell, const sf::Vector2f &position, bool can_move);
  	void add_sprite(std::queue<sf::Sprite> &tile, const sf::Vector2f &position, sf::Texture &texture);
public:
	SFMLRender(sf::RenderWindow &window);

	void render_game(const GameEngine &engine) override;
	void render_menu(const GameEngine &engine) override;
	void render(const GameEngine &engine) override;
};
