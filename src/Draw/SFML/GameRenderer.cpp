#include <queue>
#include "GameRenderer.hpp"
#include "Event/NegativeEvents/Spikes.hpp"
#include "Event/PositiveEvents/Potion.hpp"
#include "Event/MovementEvents/RandomMine.hpp"
#include "Event/PositiveEvents/ShieldKit.hpp"
#include "Event/PositiveEvents/Star.hpp"

static const std::string root = "../../resources/entities/";

static const std::vector<std::string> paths = {
	"hero.png",
	"start.png",
	"finish.png",
	"floor_tile.png",
	"wall.png",
	"door.png",
	"lock.png",
	"key.png",
	"random_mine.png",
	"spikes.png",
	"potion.png",
	"shield.png",
	"star.png"
};

GameRenderer::GameRenderer(sf::RenderWindow &parent, sf::Font &font, SfmlInput &binds) :
parent_(parent),
font_(font),
binds_(binds),
statistic_(parent.getSize(), sf::Vector2u(parent.getSize().x / 5, parent.getSize().y / 5), font_)
{
	load_textures();
	tile_size_ = sf::Vector2f(parent_.getSize().x * 1.0 / 11, parent_.getSize().y * 1.0 / 7);
}

void GameRenderer::destroy()
{
	textures_.clear();
}

void GameRenderer::load_textures()
{
	textures_.resize(paths.size());

	for (size_t i = 0; i < paths.size(); ++i)
	{
		if (!textures_[i].loadFromFile(root + paths[i]))
		{
			destroy();
			throw std::invalid_argument(std::string("Failed to initialize game textures"));
		}
	}
}

Command *GameRenderer::on_key_press(const sf::Event &event)
{
	return binds_.command(event.key.code);
}

void GameRenderer::on_exit()
{
	textures_.clear();
}

void GameRenderer::render(const GameEngine &game)
{
	parent_.clear();

	auto player = game.player();

	std::vector<std::queue<sf::Sprite>> field_;

	const sf::Vector2<int32_t> max_tiles(11, 7);
	const sf::Vector2<int32_t> mapping_offset(player->get_position().y() - max_tiles.x / 2, player->get_position().x() - max_tiles.y / 2);

	const int32_t max_cells = max_tiles.x * max_tiles.y;

	for (int32_t y = 0; y < max_tiles.y; ++y)
	{
		for (int32_t x = 0; x < max_tiles.x; ++x)
		{
			Position point(y + mapping_offset.y, x + mapping_offset.x);
			const auto &cell = game.field()->is_on_map(point) ? game.field()->get_cell(point) : Cell(Cell::WALL);
			field_.push_back(build_tile(cell, sf::Vector2f(x, y), game.field()->can_move(player, point)));

			if (field_.size() == (max_cells + 1) / 2)
			{
				add_sprite(field_.back(), sf::Vector2f(x, y), PLAYER);
			}
		}
	}

	for (auto &tile : field_)
	{
		while(!tile.empty())
		{
			parent_.draw(tile.front());
			tile.pop();
		}
	}

	statistic_.update(*player);
	parent_.draw(statistic_);

	parent_.display();
}

std::queue<sf::Sprite> GameRenderer::build_tile(const Cell &cell, const sf::Vector2f &position, bool can_move)
{
	std::queue<sf::Sprite> tile;

	if (!cell.is_movable())
	{
		add_sprite(tile, position, GAME_TEXTURE::WALL);
	}
	else
	{
		add_sprite(tile, position, GAME_TEXTURE::MOVABLE);

		if (cell.is_entrance())
		{
			add_sprite(tile, position, GAME_TEXTURE::START);
		}
		else if (cell.is_exit())
		{
			add_sprite(tile, position, GAME_TEXTURE::FINISH);
		}
		else if (cell.has_door())
		{
			add_sprite(tile, position, GAME_TEXTURE::DOOR);

			if (!can_move)
			{
				add_sprite(tile, position, GAME_TEXTURE::LOCK);
			}
		}
		else
		{
			auto *active_event = cell.get_active_event();

			if (const auto *p = dynamic_cast<const Spikes *>(active_event); p != nullptr)
			{
				add_sprite(tile, position, GAME_TEXTURE::SPIKES);
			}
			else if (const auto *k = dynamic_cast<const Potion *>(active_event); k != nullptr)
			{
				add_sprite(tile, position, GAME_TEXTURE::POTION);
			}
			else if (const auto *d = dynamic_cast<const RandomMine *>(active_event); d != nullptr)
			{
				add_sprite(tile, position, GAME_TEXTURE::RANDOM_MINE);
			}
			else if (const auto *m = dynamic_cast<const ShieldKit *>(active_event); m != nullptr)
			{
				add_sprite(tile, position, GAME_TEXTURE::SHIELD_KIT);
			}
			else if (const auto *n = dynamic_cast<const Star *>(active_event); n != nullptr)
			{
				add_sprite(tile, position, GAME_TEXTURE::STAR);
			}
			else if (const auto *t = dynamic_cast<const Key *>(active_event); t != nullptr)
			{
				add_sprite(tile, position, GAME_TEXTURE::KEY);
			}
		}
	}

	return tile;
}

void GameRenderer::add_sprite(std::queue<sf::Sprite> &tile, const sf::Vector2f &position, GAME_TEXTURE texture)
{
	sf::Sprite sprite;

	sprite.setTexture(textures_[texture]);
	sprite.setScale(tile_size_.x / textures_[texture].getSize().x, tile_size_.y / textures_[texture].getSize().y);
	sprite.setPosition(sf::Vector2f(position.x * tile_size_.x, position.y * tile_size_.y));

	tile.emplace(sprite);
}
