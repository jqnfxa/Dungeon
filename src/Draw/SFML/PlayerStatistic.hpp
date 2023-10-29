#pragma once

#include <SFML/Graphics/Text.hpp>
#include "../../Handlers/PlayerHandler/PlayerHandler.hpp"

enum STATISTIC_ALIGNMENT {
	LEFT_ALIGNMENT,
	RIGHT_ALIGNMENT
};

class PlayerStatistic : public sf::Drawable, public sf::Transformable {
  sf::Vector2u size_;
  sf::Font font_;
  int32_t text_size_;
  int32_t offset_;
  int32_t relative_offset_;
  STATISTIC_ALIGNMENT alignment_;
  const double step_coefficient_ = 1.0 / 5;

  std::vector<std::pair<sf::Text, sf::Text>> stats_;
  void reset_stats_position();
  void reset_position(std::pair<sf::Text, sf::Text> &stat, const sf::Vector2u &position);
 public:
  PlayerStatistic(const sf::Vector2u &parent_size, const sf::Vector2u &size, sf::Font &font, STATISTIC_ALIGNMENT alignment = RIGHT_ALIGNMENT);
  void update(const PlayerHandler &handler);
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};
