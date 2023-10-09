#include "OpenPlayMenu.hpp"
#include "Game/Engine/GameEngine.hpp"

void OpenPlayMenu::execute(GameEngine &game)
{
	game.open_play_menu();
}

bool OpenPlayMenu::operator==(Command *other)
{
	return dynamic_cast<OpenPlayMenu *>(other) != nullptr;
}
