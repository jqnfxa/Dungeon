#include "GoToSettings.hpp"
#include "Game/GameEngine.hpp"

void GoToSettings::execute(GameEngine &game)
{
	game.goto_settings();
}
bool GoToSettings::operator==(Command *other)
{
	return dynamic_cast<GoToSettings *>(other) != nullptr;
}
