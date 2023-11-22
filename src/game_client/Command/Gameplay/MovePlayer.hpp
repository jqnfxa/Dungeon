#pragma once

#include "../ICommand.hpp"
#include "Movement/Direction.hpp"


class MovePlayer : public ICommand
{
	DIRECTION direction_;
public:
	explicit MovePlayer(DIRECTION direction = DIRECTION::NONE);
	void execute(GameEngine &engine) override;
};
