#include "ResumeGame.hpp"
#include "Game/Engine/GameEngine.hpp"

void ResumeGame::execute(GameEngine &game)
{
	game.resume();
}

bool ResumeGame::operator==(Command *other)
{
	return dynamic_cast<ResumeGame *>(other) != nullptr;
}

std::string ResumeGame::to_str() const
{
	return "ResumeGame";
}
