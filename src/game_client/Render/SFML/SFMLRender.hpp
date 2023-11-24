#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "../IRender.hpp"
#include "World/Cell.hpp"
#include "PlayerStatistics.hpp"


class SFMLRender : public IRender
{
	static constexpr const int32_t window_width = 11;
	static constexpr const int32_t window_height = 7;

	sf::RenderWindow &window_;
	sf::Font font_;
	sf::Vector2f tile_size_;

	PlayerStatistic stats;

	sf::Texture load_texture(const std::string &full_path);
  	void load_textures();

  	std::queue<sf::Sprite> build_tile(const Cell &cell, const sf::Vector2f &position, bool can_move);
  	void add_sprite(std::queue<sf::Sprite> &tile, const sf::Vector2f &position, sf::Texture &texture);

	void render_background(IState *game_state);
	void render_player_statistics(PlayerHandler &player);
public:
	SFMLRender(sf::RenderWindow &window);

	void render_game(const GameEngine &engine) override;
	void render_menu(const GameEngine &engine) override;
	void render(const GameEngine &engine) override;
};
