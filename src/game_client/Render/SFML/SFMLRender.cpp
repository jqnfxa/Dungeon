#include "SFMLRender.hpp"
#include "State/Defines.hpp"
#include "Event/Defines.hpp"
#include "Path.hpp"

#include <iostream>
#include <typeindex>


const std::string &fonts_path = game_dir + "/fonts/";
const std::string &textures_path = game_dir + "/resources/entities/";
const std::string &menues_path = game_dir + "/resources/menues/";

std::unordered_map<std::type_index, std::pair<sf::Texture, std::string>> entity_textures_ = {
	{typeid(PlayerHandler), {{}, textures_path + "hero.png"}}
};

std::unordered_map<Cell::TYPE, std::pair<sf::Texture, std::string>> cell_textures_ = {
	{Cell::TYPE::ENTRANCE, {{}, textures_path + "start.png"}},
	{Cell::TYPE::EXIT, {{}, textures_path + "finish.png"}},
	{Cell::TYPE::MOVABLE, {{}, textures_path + "floor_tile.png"}},
	{Cell::TYPE::WALL, {{}, textures_path + "wall.png"}}
};

std::unordered_map<std::type_index, std::pair<sf::Texture, std::string>> event_textures_ = {
	{typeid(RandomMine), {{}, textures_path + "random_mine.png"}},
	{typeid(Spikes), {{}, textures_path + "spikes.png"}},
	{typeid(Potion), {{}, textures_path + "potion.png"}},
	{typeid(ShieldKit), {{}, textures_path + "shield.png"}},
	{typeid(Star), {{}, textures_path + "star.png"}}
};

std::unordered_map<std::type_index, std::pair<sf::Texture, std::string>> menu_textures_ = {
	{typeid(MainMenuState), {{}, menues_path + "main_menu.png"}},
	{typeid(PlayMenu), {{}, menues_path + "play_menu.png"}},
	{typeid(Options), {{}, menues_path + "settings.png"}},
	{typeid(HoldState), {{}, menues_path + "trash.png"}},
	{typeid(Win), {{}, menues_path + "win.png"}},
	{typeid(Lose), {{}, menues_path + "lose.png"}}
};

SFMLRender::SFMLRender(sf::RenderWindow &window)
	: window_(window)
	, font_()
	, tile_size_(sf::Vector2f(window_.getSize().x * 1.0 / window_width, window_.getSize().y * 1.0 / window_height))
	, stats()
{
	if (!font_.loadFromFile(fonts_path + "arial.ttf"))
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
	entity_textures_.at(typeid(PlayerHandler)).first.loadFromFile(entity_textures_.at(typeid(PlayerHandler)).second);

	for (auto &[key, value] : cell_textures_)
	{
		value.first.loadFromFile(value.second);
	}

	for (auto &[key, value] : event_textures_)
	{
		value.first.loadFromFile(value.second);
	}

	for (auto &[key, value] : menu_textures_)
	{
		value.first.loadFromFile(value.second);
	}
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
				add_sprite(field_.back(), sf::Vector2f(x, y), entity_textures_.at(typeid(*player)).first);
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
		add_sprite(tile, position, cell_textures_.at(Cell::TYPE::MOVABLE).first);
	}

	add_sprite(tile, position, cell_textures_.at(cell.type()).first);

	if (const auto *active_event = cell.get_active_event(); active_event != nullptr)
	{
		add_sprite(tile, position, event_textures_.at(typeid(*active_event)).first);
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
	background.setTexture(&menu_textures_.at(typeid(*game_state)).first);
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
	if (!engine.is_running() || engine.get_state() == nullptr)
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
