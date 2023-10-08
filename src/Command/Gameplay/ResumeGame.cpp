#include "ResumeGame.hpp"
#include "Game/GameEngine.hpp"

void ResumeGame::execute(GameEngine &game)
{
	game.resume();
}

bool ResumeGame::operator==(Command *other)
{
	return dynamic_cast<ResumeGame *>(other) != nullptr;
}