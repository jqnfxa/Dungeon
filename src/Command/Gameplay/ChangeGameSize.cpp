#include "ChangeGameSize.hpp"
#include "Game/GameEngine.hpp"

ChangeGameSize::ChangeGameSize(MAP_SIZE size) : size_(size)
{
}

void ChangeGameSize::execute(GameEngine &game)
{
	game.goto_play_menu();
	game.set_game_size(size_);
}
bool ChangeGameSize::operator==(Command *other)
{
	return dynamic_cast<ChangeGameSize *>(other) != nullptr;
}