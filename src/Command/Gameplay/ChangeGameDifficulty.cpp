#include "ChangeGameDifficulty.hpp"
#include "Game/GameEngine.hpp"

ChangeGameDifficulty::ChangeGameDifficulty(DIFFICULTY difficulty) : difficulty_(difficulty)
{
}

void ChangeGameDifficulty::execute(GameEngine &game)
{
	game.open_settings();
	game.set_game_difficulty(difficulty_);
}

bool ChangeGameDifficulty::operator==(Command *other)
{
	return dynamic_cast<ChangeGameDifficulty *>(other) != nullptr;
}
