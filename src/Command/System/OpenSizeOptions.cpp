#include "OpenSizeOptions.hpp"
#include "Game/Engine/GameEngine.hpp"

void OpenSizeOptions::execute(GameEngine &game)
{
	game.open_size_options();
}

bool OpenSizeOptions::operator==(Command *other)
{
	return dynamic_cast<OpenSizeOptions *>(other) != nullptr;
}

std::string OpenSizeOptions::to_str() const
{
	return "OpenSizeOptions";
}
