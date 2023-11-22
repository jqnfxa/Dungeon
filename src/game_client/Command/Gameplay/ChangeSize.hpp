#pragma once

#include "../ICommand.hpp"
#include "MapGenerator/DefaultLevels/DefaultLevelGenerator.hpp"


class ChangeSize : public ICommand
{
	MAP_SIZE size_;
public:
	explicit ChangeSize(MAP_SIZE size = MAP_SIZE::SMALL);
	void execute(GameEngine &engine) override;
};
