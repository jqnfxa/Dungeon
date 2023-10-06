#include <iostream>
#include "GameFieldDrawer.hpp"
#include "Command/Factory/CommandFactory.hpp"
#include "Event/NegativeEvents/Spikes.hpp"
#include "Event/PositiveEvents/Potion.hpp"
#include "Event/MovementEvents/RandomMine.hpp"
#include "Event/PositiveEvents/ShieldKit.hpp"
#include "Event/PositiveEvents/Star.hpp"

GameFieldDrawer::GameFieldDrawer(sf::RenderWindow &parent, GameEngine &game, const std::unordered_map<TILE_TYPE, sf::Texture> &textures) : render_window_(parent),
																																		   game_engine_(game),
																																		   textures_(textures)
{
	render_map_.resize(7);

	for (auto &line: render_map_)
	{
		line.resize(11);
	}

	tile_size_ = sf::Vector2f(parent.getSize().x * 1.0 / 11, parent.getSize().y * 1.0 / 7);

	if (!font_.loadFromFile("../../resources/fonts/arial.ttf"))
	{
		throw std::logic_error("Failed to load font");
	}

	sf::Vector2f text_pos(parent.getSize().x * 2 / 3, parent.getSize().y / 20);
	int32_t size = parent.getSize().y / 15;
	int32_t step = size / 10;

	add_text_field(stats_, font_, "Health", size, sf::Color::White, text_pos);
	text_pos.y += size + step;
	add_text_field(stats_, font_, "Armor", size, sf::Color::White, text_pos);
	text_pos.y += size + step;
	add_text_field(stats_, font_, "Attack", size, sf::Color::White, text_pos);
	text_pos.y += size + step;
	add_text_field(stats_, font_, "Defence", size, sf::Color::White, text_pos);
	text_pos.y += size + step;
	add_text_field(stats_, font_, "Points", size, sf::Color::White, text_pos);

	// health
	// armor
	// attack
	// defence
	// points
}

GameFieldDrawer::~GameFieldDrawer() = default;

Command *GameFieldDrawer::on_key_press(const sf::Event &event)
{
	// TODO process only config buttons
	Command *cmd;

	switch (event.key.code)
	{
		case sf::Keyboard::A: cmd = CommandFactory::instance().create(COMMAND::MOVE_LEFT);
			break;
		case sf::Keyboard::W: cmd = CommandFactory::instance().create(COMMAND::MOVE_UP);
			break;
		case sf::Keyboard::S: cmd = CommandFactory::instance().create(COMMAND::MOVE_DOWN);
			break;
		case sf::Keyboard::D: cmd = CommandFactory::instance().create(COMMAND::MOVE_RIGHT);
			break;
		case sf::Keyboard::Escape: cmd = CommandFactory::instance().create(COMMAND::OPEN_HOLD_MENU);
			break;
		case sf::Keyboard::Return: cmd = CommandFactory::instance().create(COMMAND::RETURN_TO_MENU);
			break;
		default: cmd = CommandFactory::instance().create(COMMAND::EMPTY_OPERATION);
			break;
	}

	return cmd;
}

void GameFieldDrawer::draw()
{
	render_window_.clear();

	auto player_position = game_engine_.player()->get_position();

	sf::Vector2f pos;

	for (int32_t r = 0; r < render_map_.size(); ++r)
	{
		for (int32_t c = 0; c < render_map_[r].size(); ++c)
		{
			pos.x = static_cast<float>(c);
			pos.y = static_cast<float>(r);

			Position point(r + player_position.x() - 3, c + player_position.y() - 5);

			if (!game_engine_.field()->is_on_map(point))
			{
				build_tile(render_map_[r][c], pos, Cell(Cell::WALL), false);
			}
			else
			{
				bool can_move = game_engine_.field()->can_move(game_engine_.player(), point);
				build_tile(render_map_[r][c], pos, game_engine_.field()->get_cell(point), can_move);
			}
			if (r == (render_map_.size() / 2) && c == (render_map_[r].size() / 2))
			{
				add_sprite(render_map_[r][c], pos, textures_[TILE_TYPE::PLAYER]);
			}
		}
	}

	for (auto &line: render_map_)
	{
		for (auto &cell: line)
		{
			while (!cell.empty())
			{
				render_window_.draw(cell.front());
				cell.pop();
			}
		}
	}

	std::vector<int32_t> player_stats;

	player_stats.push_back(game_engine_.player()->get_health());
	player_stats.push_back(game_engine_.player()->get_armor());
	player_stats.push_back(game_engine_.player()->get_attack());
	player_stats.push_back(game_engine_.player()->get_defense());
	player_stats.push_back(game_engine_.player()->get_points());
	int32_t step = render_window_.getSize().x / 5;

	for (size_t i = 0; i < stats_.size(); ++i)
	{
		render_window_.draw(stats_[i]);

		sf::Text value = stats_[i];
		value.setString(std::to_string(player_stats[i]));
		value.setPosition(value.getPosition().x + step, value.getPosition().y);
		render_window_.draw(value);
	}

	render_window_.display();
}

void GameFieldDrawer::build_tile(std::queue<sf::Sprite> &tile, const sf::Vector2f &position, const Cell &cell, bool can_move)
{
	if (!cell.is_movable())
	{
		add_sprite(tile, position, textures_[TILE_TYPE::IS_CLOSED]);
	}
	else
	{
		add_sprite(tile, position, textures_[TILE_TYPE::IS_OPEN]);

		if (cell.is_entrance())
		{
			add_sprite(tile, position, textures_[TILE_TYPE::IS_START]);
		}
		else if (cell.is_exit())
		{
			add_sprite(tile, position, textures_[TILE_TYPE::IS_FINISH]);
		}
		else if (cell.has_door())
		{
			add_sprite(tile, position, textures_[TILE_TYPE::HAS_DOOR]);

			if (!can_move)
			{
				add_sprite(tile, position, textures_[TILE_TYPE::DOOR_LOCKED]);
			}
		}
		else
		{
			auto *active_event = cell.get_active_event();

			if (const auto *p = dynamic_cast<const Spikes *>(active_event); p != nullptr)
			{
				add_sprite(tile, position, textures_[TILE_TYPE::HAS_SPIKES]);
			}
			else if (const auto *k = dynamic_cast<const Potion *>(active_event); k != nullptr)
			{
				add_sprite(tile, position, textures_[TILE_TYPE::HAS_POTION]);
			}
			else if (const auto *d = dynamic_cast<const RandomMine *>(active_event); d != nullptr)
			{
				add_sprite(tile, position, textures_[TILE_TYPE::HAS_RANDOM_MINE]);
			}
			else if (const auto *m = dynamic_cast<const ShieldKit *>(active_event); m != nullptr)
			{
				add_sprite(tile, position, textures_[TILE_TYPE::HAS_SHIELD_KIT]);
			}
			else if (const auto *n = dynamic_cast<const Star *>(active_event); n != nullptr)
			{
				add_sprite(tile, position, textures_[TILE_TYPE::HAS_STAR]);
			}
			else if (const auto *t = dynamic_cast<const Key *>(active_event); t != nullptr)
			{
				add_sprite(tile, position, textures_[TILE_TYPE::HAS_KEY]);
			}
		}
	}
}

void GameFieldDrawer::add_sprite(std::queue<sf::Sprite> &tile, const sf::Vector2f &position, const sf::Texture &texture)
{
	sf::Sprite sprite;

	sprite.setTexture(texture);
	sprite.setScale(tile_size_.x / texture.getSize().x, tile_size_.y / texture.getSize().y);
	sprite.setPosition(sf::Vector2f(position.x * tile_size_.x, position.y * tile_size_.y));

	tile.emplace(sprite);
}
void GameFieldDrawer::add_text_field(std::vector<sf::Text> &stats, const sf::Font &font, const std::string &str, int32_t size, const sf::Color &color, const sf::Vector2f &position)
{
	sf::Text field;
	field.setOutlineColor(sf::Color::Black);
	field.setOutlineThickness(3);
	field.setFont(font);
	field.setString(str);
	field.setCharacterSize(size);
	field.setFillColor(color);
	field.setPosition(position);
	stats.emplace_back(field);
}
