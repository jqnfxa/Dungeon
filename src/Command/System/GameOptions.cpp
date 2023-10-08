#include "GameOptions.hpp"
#include "Game/GameEngine.hpp"

void GameOptions::execute(GameEngine &game)
{
	game.open_settings();
}

bool GameOptions::operator==(Command *other)
{
	return dynamic_cast<GameOptions *>(other) != nullptr;
}
