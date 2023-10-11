#include "ChangeFieldSize.hpp"
#include "Game/Engine/GameEngine.hpp"

ChangeFieldSize::ChangeFieldSize() : ChangeFieldSize(SMALL)
{
}

ChangeFieldSize::ChangeFieldSize(MAP_SIZE size) : size_(size)
{
}

void ChangeFieldSize::execute(GameEngine &game)
{
	game.resize_filed(size_);
}

bool ChangeFieldSize::operator==(Command *other)
{
	return dynamic_cast<ChangeFieldSize *>(other) != nullptr;
}

std::string ChangeFieldSize::to_str() const
{
	return "Change field size to " + std::to_string(size_);
}
