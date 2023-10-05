#include "ChangeGameDifficulty.hpp"
#include "Game/GameEngine.hpp"

ChangeGameDifficulty::ChangeGameDifficulty(DIFFICULTY difficulty) : difficulty_(difficulty)
{
}

void ChangeGameDifficulty::execute(GameEngine &game)
{
	game.goto_play_menu();
	game.set_game_difficulty(difficulty_);
}

bool ChangeGameDifficulty::operator==(Command *other)
{
	return dynamic_cast<ChangeGameDifficulty *>(other) != nullptr;
}
