#pragma once

#include <istream>
#include <fstream>
#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "Input/Base/InputModel.hpp"


class SFMLInput : public InputModel {
	sf::RenderWindow &window_;
	std::ifstream file_;
public:
	explicit SFMLInput(const std::string &config_path, sf::RenderWindow &window);

	void update() override;
};
