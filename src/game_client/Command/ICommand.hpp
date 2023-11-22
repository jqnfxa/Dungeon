#pragma once


class GameEngine;
class ICommand
{
public:
	virtual ~ICommand() = default;
	virtual void execute(GameEngine &engine) = 0;
};
