#include "Win.hpp"
#include "Command/Defines.hpp"

#include <iostream>

Win::Win() : menu_()
{
	menu_.add_label("next level");
	menu_.add_label("menu");

	menu_.add_item("next level", new CreateSession);
	menu_.add_item("menu", new OpenMainMenu);
}

Menu *Win::menu()
{
	return &menu_;
}

bool Win::handle_command(GameEngine &engine, ICommand *command)
{
	if (command == nullptr)
	{
		return false;
	}

	bool is_handled = false;

	if (typeid(*command) == typeid(CreateSession) ||
		typeid(*command) == typeid(OpenMainMenu) ||
		typeid(*command) == typeid(ScrollDown) ||
		typeid(*command) == typeid(ScrollUp) ||
		typeid(*command) == typeid(Select) ||
		typeid(*command) == typeid(Terminate))
	{
		command->execute(engine);

		is_handled = true;
	}

	return is_handled;
}
