#pragma once

#include "../ICommand.hpp"
#include "MapGenerator/DefaultLevels/DefaultLevelGenerator.hpp"


class ChangeDifficulty : public ICommand
{
	DIFFICULTY difficulty_;
public:
	explicit ChangeDifficulty(DIFFICULTY difficulty = DIFFICULTY::EASY);
	void execute(GameEngine &engine) override;
};
