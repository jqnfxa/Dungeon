#include "ReturnToMenu.hpp"
#include "Game/GameEngine.hpp"

void ReturnToMenu::execute(GameEngine &game)
{
	game.exit_to_menu();
}
bool ReturnToMenu::operator==(Command *other)
{
	return dynamic_cast<ReturnToMenu *>(other) != nullptr;
}
