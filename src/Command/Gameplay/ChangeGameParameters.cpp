#include "ChangeGameParameters.hpp"
#include "Game/GameEngine.hpp"

ChangeGameParameters::ChangeGameParameters(MAP_SIZE size, DIFFICULTY difficulty) : size_(size), difficulty_(difficulty)
{
}

void ChangeGameParameters::execute(GameEngine &game)
{
	game.set_game_size(size_);
	game.set_game_difficulty(difficulty_);
}

bool ChangeGameParameters::operator==(Command *other)
{
	return dynamic_cast<ChangeGameParameters *>(other) != nullptr;
}
