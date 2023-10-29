#include <SFML/Graphics.hpp>
#include <iostream>
#include "PlayerStatistic.hpp"

PlayerStatistic::PlayerStatistic(const sf::Vector2u &parent_size,
								 const sf::Vector2u &size,
								 sf::Font &font,
								 STATISTIC_ALIGNMENT alignment) :
								 size_(size),
								 font_(font),
								 text_size_(1),
								 offset_(0),
								 alignment_(alignment)
{
	// Note that player have only 5 stats
	const int stats_count = 5;
	text_size_ = static_cast<int32_t>(size_.y / (stats_count + stats_count * step_coefficient_ - step_coefficient_));
	offset_ = alignment_ == RIGHT_ALIGNMENT ? parent_size.x - size.x : 0;
	relative_offset_ = size.x / 2;

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

	for (auto &stat : stats_)
	{
		target.draw(stat.first, states);
		target.draw(stat.second, states);
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
	auto &lhs = stat.first;
	auto &rhs = stat.second;

	lhs.setPosition(position.x, position.y);
	rhs.setPosition(position.x + relative_offset_, position.y);
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
