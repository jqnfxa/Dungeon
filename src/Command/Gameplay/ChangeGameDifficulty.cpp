#include "ChangeGameDifficulty.hpp"
#include "Game/Engine/GameEngine.hpp"

ChangeGameDifficulty::ChangeGameDifficulty() : ChangeGameDifficulty(EASY)
{
}

ChangeGameDifficulty::ChangeGameDifficulty(DIFFICULTY difficulty) : difficulty_(difficulty)
{
}

void ChangeGameDifficulty::execute(GameEngine &game)
{
	game.change_difficulty(difficulty_);
}

bool ChangeGameDifficulty::operator==(Command *other)
{
	return dynamic_cast<ChangeGameDifficulty *>(other) != nullptr;
}