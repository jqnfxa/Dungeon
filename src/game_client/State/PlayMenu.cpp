#include "PlayMenu.hpp"
#include "Command/Defines.hpp"


PlayMenu::PlayMenu() : menu_()
{
	menu_.add_label("new game");
	menu_.add_label("menu");

	menu_.add_item("new game", new CreateSession);
	menu_.add_item("menu", new OpenMainMenu);
}

Menu *PlayMenu::menu()
{
	return &menu_;
}

bool PlayMenu::handle_command(GameEngine &engine, ICommand *command)
{
	if (command == nullptr)
	{
		return false;
	}

	bool is_handled = false;

	if (processable.contains(typeid(*command)))
	{
		command->execute(engine);
		is_handled = true;
	}

	return is_handled;
}
