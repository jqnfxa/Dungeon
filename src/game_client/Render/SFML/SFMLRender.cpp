#include "SFMLRender.hpp"
#include "State/Defines.hpp"
#include "Event/Defines.hpp"

#include <iostream>
#include <typeindex>

const std::string &root = "/home/shard/.dungeon/fonts/";
const std::string &root_textures = "/home/shard/.dungeon/resources/entities/";
const std::string &root_menues = "/home/shard/.dungeon/resources/menues/";

static const std::vector<std::string> paths = {
	"hero.png",
	"start.png",
	"finish.png",
	"floor_tile.png",
	"wall.png",
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
	{typeid(RandomMine), {}},
	{typeid(Spikes), {}},
	{typeid(Potion), {}},
	{typeid(ShieldKit), {}},
	{typeid(Star), {}}
};

std::unordered_map<std::type_index, sf::Texture> menu_textures_ = {
	{typeid(MainMenuState), {}},
	{typeid(PlayMenu), {}},
	{typeid(Options), {}},
	{typeid(HoldState), {}},
	{typeid(Win), {}},
	{typeid(Lose), {}}
};

SFMLRender::SFMLRender(sf::RenderWindow &window)
	: window_(window)
	, font_()
	, tile_size_(sf::Vector2f(window_.getSize().x * 1.0 / window_width, window_.getSize().y * 1.0 / window_height))
	, stats()
{
	if (!font_.loadFromFile(root + "arial.ttf"))
	{
		throw std::runtime_error("Failed to load font");
	}

	load_textures();
	stats.initialize(window.getSize(), sf::Vector2u(window.getSize().x / 5, window.getSize().y / 5), font_);
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
	entity_textures_.at(typeid(PlayerHandler)).loadFromFile(root_textures + "hero.png");

	cell_textures_.at(Cell::TYPE::ENTRANCE).loadFromFile(root_textures + "start.png");
	cell_textures_.at(Cell::TYPE::EXIT).loadFromFile(root_textures + "finish.png");
	cell_textures_.at(Cell::TYPE::MOVABLE).loadFromFile(root_textures + "floor_tile.png");
	cell_textures_.at(Cell::TYPE::WALL).loadFromFile(root_textures + "wall.png");

	event_textures_.at(typeid(RandomMine)).loadFromFile(root_textures + "random_mine.png");
	event_textures_.at(typeid(Spikes)).loadFromFile(root_textures + "spikes.png");
	event_textures_.at(typeid(Potion)).loadFromFile(root_textures + "potion.png");
	event_textures_.at(typeid(ShieldKit)).loadFromFile(root_textures + "shield.png");
	event_textures_.at(typeid(Star)).loadFromFile(root_textures + "star.png");

	menu_textures_.at(typeid(MainMenuState)).loadFromFile(root_menues + "main_menu.png");
	menu_textures_.at(typeid(PlayMenu)).loadFromFile(root_menues + "play_menu.png");
	menu_textures_.at(typeid(Options)).loadFromFile(root_menues + "settings.png");
	menu_textures_.at(typeid(HoldState)).loadFromFile(root_menues + "trash.png");
	menu_textures_.at(typeid(Win)).loadFromFile(root_menues + "win.png");
	menu_textures_.at(typeid(Lose)).loadFromFile(root_menues + "lose.png");
}

void SFMLRender::render_game(const GameEngine &game)
{
	window_.clear();

	auto player = game.player();

	std::vector<std::queue<sf::Sprite>> field_;

	const sf::Vector2<int32_t> max_tiles(window_width, window_height);
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

	render_player_statistics(*player);

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

void SFMLRender::render_background(IState *game_state)
{
	if (game_state == nullptr)
	{
		return;
	}

	sf::RectangleShape background;

	background.setSize(sf::Vector2f(window_.getSize().x, window_.getSize().y));
	background.setTexture(&menu_textures_.at(typeid(*game_state)));
	background.setPosition(0, 0);

	window_.draw(background);
}

void SFMLRender::render_player_statistics(PlayerHandler &player)
{
	stats.update(player);
	window_.draw(stats);
}

void SFMLRender::render_menu(const GameEngine &engine)
{
	window_.clear();

	// render background
	render_background(engine.get_state());

	sf::Vector2u available_space = window_.getSize();
	auto &labels = engine.get_state()->menu()->labels_;

	for (size_t i = 0; i < labels.size(); ++i)
	{
		sf::Text label(labels[i].label, font_);
		label.setOutlineColor(sf::Color::Black);
		label.setOutlineThickness(3);
		label.setCharacterSize(available_space.x / labels.size() / 3);

		auto label_bounds = label.getLocalBounds();

		if(i == engine.get_state()->menu()->selected_)
		{
			label.setFillColor(sf::Color::Red);
		}

		if (labels[i].options.size() > 1)
		{
			for (size_t j = 0; j < labels[i].options.size(); ++j)
			{
				sf::Text choosen("*", font_);

				if (j == labels[i].selected)
				{
					choosen.setFillColor(sf::Color::Red);
				}

				auto cur_bound = choosen.getLocalBounds();
				sf::Vector2f position(available_space.x / 2.0f + label_bounds.width + (j + 1) * cur_bound.width, (i + 1) * (available_space.y / (labels.size() + 1)) - cur_bound.height);

				choosen.setPosition(position);
				window_.draw(choosen);
			}
		}

		label.setOrigin(label_bounds.left + label_bounds.width / 2.0f, label_bounds.top + label_bounds.height / 2.0f);
		label.setPosition(sf::Vector2f(available_space.x / 2.0f, (i + 1) * (available_space.y / (labels.size() + 1))));
		window_.draw(label);
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
