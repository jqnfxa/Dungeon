#include "SFMLRender.hpp"
#include "State/Defines.hpp"
#include "Event/Defines.hpp"

#include <iostream>
#include <typeindex>

const std::string &root = "/home/shard/.dungeon/fonts/";
const std::string &root_textures = "/home/shard/.dungeon/resources/entities/";

static const std::vector<std::string> paths = {
	"hero.png",
	"start.png",
	"finish.png",
	"floor_tile.png",
	"wall.png",
	"door.png",
	"key.png",
	"random_mine.png",
	"spikes.png",
	"potion.png",
	"shield.png",
	"star.png"
};

std::unordered_map<std::type_index, sf::Texture> entity_textures_ = {
	{typeid(PlayerHandler), {}}
};

std::unordered_map<Cell::TYPE, sf::Texture> cell_textures_ = {
	{Cell::TYPE::ENTRANCE, {}},
	{Cell::TYPE::EXIT, {}},
	{Cell::TYPE::MOVABLE, {}},
	{Cell::TYPE::WALL, {}}
};

std::unordered_map<std::type_index, sf::Texture> event_textures_ = {
	{typeid(Door), {}},
	{typeid(Key), {}},
	{typeid(RandomMine), {}},
	{typeid(Spikes), {}},
	{typeid(Potion), {}},
	{typeid(ShieldKit), {}},
	{typeid(Star), {}}
};

SFMLRender::SFMLRender(sf::RenderWindow &window) : window_(window), font_()
{
	if (!font_.loadFromFile(root + "arial.ttf"))
	{
		throw std::runtime_error("Failed to load font");
	}

	load_textures();
	tile_size_ = sf::Vector2f(window_.getSize().x * 1.0 / 11, window_.getSize().y * 1.0 / 7);
}

sf::Texture SFMLRender::load_texture(const std::string &full_path)
{
	sf::Texture texture;

	if (!texture.loadFromFile(full_path))
	{
		throw std::invalid_argument(std::string("Failed to initialize texture: " + full_path));
	}

	return texture;
}

void SFMLRender::load_textures()
{
	entity_textures_[typeid(PlayerHandler)].loadFromFile(root_textures + "hero.png");

	// TODO: remove key/door/lock
	cell_textures_.at(Cell::TYPE::ENTRANCE).loadFromFile(root_textures + "start.png");
	cell_textures_.at(Cell::TYPE::EXIT).loadFromFile(root_textures + "finish.png");
	cell_textures_.at(Cell::TYPE::MOVABLE).loadFromFile(root_textures + "floor_tile.png");
	cell_textures_.at(Cell::TYPE::WALL).loadFromFile(root_textures + "wall.png");

	event_textures_[typeid(Door)].loadFromFile(root_textures + "door.png");
	event_textures_[typeid(Key)].loadFromFile(root_textures + "key.png");
	event_textures_[typeid(RandomMine)].loadFromFile(root_textures + "random_mine.png");
	event_textures_[typeid(Spikes)].loadFromFile(root_textures + "spikes.png");
	event_textures_[typeid(Potion)].loadFromFile(root_textures + "potion.png");
	event_textures_[typeid(ShieldKit)].loadFromFile(root_textures + "shield.png");
	event_textures_[typeid(Star)].loadFromFile(root_textures + "star.png");
}

void SFMLRender::render_game(const GameEngine &game)
{
	window_.clear();

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
				add_sprite(field_.back(), sf::Vector2f(x, y), entity_textures_.at(typeid(*player)));
			}
		}
	}

	for (auto &tile : field_)
	{
		while(!tile.empty())
		{
			window_.draw(tile.front());
			tile.pop();
		}
	}

	//statistic_.update(*player);

	window_.display();
}

std::queue<sf::Sprite> SFMLRender::build_tile(const Cell &cell, const sf::Vector2f &position, bool can_move)
{
	std::queue<sf::Sprite> tile;

	if (cell.is_entrance() || cell.is_exit())
	{
		add_sprite(tile, position, cell_textures_.at(Cell::TYPE::MOVABLE));
	}

	add_sprite(tile, position, cell_textures_.at(cell.type()));

	if (const auto *active_event = cell.get_active_event(); active_event != nullptr)
	{
		add_sprite(tile, position, event_textures_.at(typeid(*active_event)));
	}

	return tile;
}

void SFMLRender::add_sprite(std::queue<sf::Sprite> &tile, const sf::Vector2f &position, sf::Texture &texture)
{
	sf::Sprite sprite;

	sprite.setTexture(texture);
	sprite.setScale(tile_size_.x / texture.getSize().x, tile_size_.y / texture.getSize().y);
	sprite.setPosition(sf::Vector2f(position.x * tile_size_.x, position.y * tile_size_.y));

	tile.emplace(sprite);
}

void SFMLRender::render_menu(const GameEngine &engine)
{
	window_.clear();

	sf::Vector2u available_space = window_.getSize();
	auto &labels = engine.get_state()->menu()->labels_;
	sf::FloatRect bounds;

	for (size_t i = 0; i < labels.size(); ++i)
	{
		sf::Text text(labels[i].label, font_);

		if(i == engine.get_state()->menu()->selected_)
		{
			text.setFillColor(sf::Color::Red);
		}

		bounds = text.getLocalBounds();

		for (size_t j = 0; j < labels[i].selected; ++j)
		{
			sf::Text text1("*", font_);
			text1.setOrigin(bounds.left + bounds.width / 2.0f + (j + 2) * (text1.getLocalBounds().width), bounds.top + bounds.height / 2.0f);
			text1.setPosition(sf::Vector2f(available_space.x / 2.0f, (i + 1) * (available_space.y / (labels.size() + 1))));
			window_.draw(text1);
		}

		text.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
		text.setPosition(sf::Vector2f(available_space.x / 2.0f, (i + 1)*(available_space.y / (labels.size() + 1))));

		window_.draw(text);
	}

	window_.display();
}

void SFMLRender::render(const GameEngine &engine)
{
	if (!engine.is_running())
	{
		return;
	}
	if (typeid(*engine.get_state()) == typeid(Play))
	{
		render_game(engine);
	}
	else
	{
		render_menu(engine);
	}
}
