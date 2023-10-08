#include "OpenHoldMenu.hpp"
#include "Game/GameEngine.hpp"

void OpenHoldMenu::execute(GameEngine &game)
{
	game.open_hold_menu();
}

bool OpenHoldMenu::operator==(Command *other)
{
	return dynamic_cast<OpenHoldMenu *>(other) != nullptr;
}
