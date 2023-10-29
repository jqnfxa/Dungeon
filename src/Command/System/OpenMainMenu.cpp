#include "OpenMainMenu.hpp"
#include "Game/Engine/GameEngine.hpp"

void OpenMainMenu::execute(GameEngine &game)
{
	game.open_main_menu();
}

bool OpenMainMenu::operator==(Command *other)
{
	return dynamic_cast<OpenMainMenu *>(other) != nullptr;
}

std::string OpenMainMenu::to_str() const
{
	return "OpenMainMenu";
}
