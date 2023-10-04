#include "TriggerHoldMenu.hpp"
#include "Game/GameEngine.hpp"

void TriggerHoldMenu::execute(GameEngine &game)
{
	game.goto_hold_menu();
}
bool TriggerHoldMenu::operator==(Command *other)
{
	return dynamic_cast<TriggerHoldMenu *>(other) != nullptr;
}
