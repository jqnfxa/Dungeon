#include "ChangeFieldSize.hpp"
#include "Game/GameEngine.hpp"

ChangeFieldSize::ChangeFieldSize(MAP_SIZE size) : size_(size)
{
}

void ChangeFieldSize::execute(GameEngine &game)
{
	game.open_settings();
	game.set_game_size(size_);
}

bool ChangeFieldSize::operator==(Command *other)
{
	return dynamic_cast<ChangeFieldSize *>(other) != nullptr;
}
