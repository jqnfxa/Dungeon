#include "OpenDifficultyOptions.hpp"
#include "Game/Engine/GameEngine.hpp"

void OpenDifficultyOptions::execute(GameEngine &game)
{
	game.open_difficulty_options();
}

bool OpenDifficultyOptions::operator==(Command *other)
{
	return dynamic_cast<OpenDifficultyOptions *>(other) != nullptr;
}

std::string OpenDifficultyOptions::to_str() const
{
	return "OpenDifficultyOptions";
}
