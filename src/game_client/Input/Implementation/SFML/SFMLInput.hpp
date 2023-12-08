#pragma once

#include <istream>
#include <fstream>
#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "Input/Base/InputModel.hpp"
#include "Logger/MessageBus.hpp"


class SFMLInput : public InputModel {
	sf::RenderWindow &window_;
	std::ifstream file_;
	MessageBus &logger_;
public:
	explicit SFMLInput(const std::string &config_path, sf::RenderWindow &window, MessageBus &logger);

	void update() override;
};
