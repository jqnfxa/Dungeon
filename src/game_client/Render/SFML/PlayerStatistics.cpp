#include <SFML/Graphics.hpp>
#include <iostream>
#include "PlayerStatistics.hpp"

PlayerStatistic::PlayerStatistic() = default;

void PlayerStatistic::initialize(const sf::Vector2u &parent_size,
				const sf::Vector2u &size,
				sf::Font &font,
				STATISTIC_ALIGNMENT alignment)
{
	size_ = size;
	font_ = font;
	text_size_ = size.y / (stats_count + stats_count * step_coefficient_ - step_coefficient_);
	offset_ = alignment == RIGHT_ALIGNMENT ? parent_size.x - size.x : 0;
	relative_offset_ = size.x / 2;
	alignment_ = alignment;

	stats_.emplace_back(sf::Text("Health", font_, text_size_), sf::Text("?", font_, text_size_));
	stats_.emplace_back(sf::Text("Armor", font_, text_size_), sf::Text("?", font_, text_size_));
	stats_.emplace_back(sf::Text("Attack", font_, text_size_), sf::Text("?", font_, text_size_));
	stats_.emplace_back(sf::Text("Defense", font_, text_size_), sf::Text("?", font_, text_size_));
	stats_.emplace_back(sf::Text("Points", font_, text_size_), sf::Text("?", font_, text_size_));

	reset_stats_position();
}

void PlayerStatistic::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	for (auto &[label, value] : stats_)
	{
		target.draw(label, states);
		target.draw(value, states);
	}
}

void PlayerStatistic::update(const PlayerHandler &handler)
{
	stats_[0].second.setString(std::to_string(handler.get_health()));
	stats_[1].second.setString(std::to_string(handler.get_armor()));
	stats_[2].second.setString(std::to_string(handler.get_attack()));
	stats_[3].second.setString(std::to_string(handler.get_defense()));
	stats_[4].second.setString(std::to_string(handler.get_points()));

	reset_stats_position();
}

void PlayerStatistic::reset_position(std::pair<sf::Text, sf::Text> &stat, const sf::Vector2u &position)
{
	auto &[label, value] = stat;

	label.setPosition(position.x, position.y);
	value.setPosition(position.x + relative_offset_, position.y);
}

void PlayerStatistic::reset_stats_position()
{
	sf::Vector2u position(offset_, 0);

	for (auto &stat : stats_)
	{
		reset_position(stat, position);
		position.y += text_size_ + (text_size_ * step_coefficient_);
	}
}
