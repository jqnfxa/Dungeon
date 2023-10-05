#include "TriggerPlayMenu.hpp"
#include "Game/GameEngine.hpp"

void TriggerPlayMenu::execute(GameEngine &game)
{
	game.goto_play_menu();
}
bool TriggerPlayMenu::operator==(Command *other)
{
	return dynamic_cast<TriggerPlayMenu *>(other) != nullptr;
}
