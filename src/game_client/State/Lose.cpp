#include "Lose.hpp"
#include "Command/Defines.hpp"


Lose::Lose() : menu_()
{
	menu_.add_label("restart");
	menu_.add_label("menu");

	menu_.add_item("restart", new RestartSession);
	menu_.add_item("menu", new OpenMainMenu);
}

Menu *Lose::menu()
{
	return &menu_;
}

bool Lose::handle_command(GameEngine &engine, ICommand *command)
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
