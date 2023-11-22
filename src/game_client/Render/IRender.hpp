#pragma once

#include "Engine/GameEngine.hpp"


class IRender
{
public:
	virtual ~IRender() = default;
	virtual void render_game(const GameEngine &game) = 0;
	virtual void render_menu(const GameEngine &game) = 0;
	virtual void render(const GameEngine &game) = 0;
};
