#include "Pause.hpp"
#include "Command/Defines.hpp"


HoldState::HoldState() : menu_()
{
	menu_.add_label("continue");
	menu_.add_label("restart");
	menu_.add_label("menu");

	menu_.add_item("continue", new ResumeGame);
	menu_.add_item("restart", new RestartSession);
	menu_.add_item("menu", new OpenMainMenu);
}

Menu *HoldState::menu()
{
	return &menu_;
}

bool HoldState::handle_command(GameEngine &engine, ICommand *command)
{
	if (command == nullptr)
	{
		return false;
	}

	bool is_handled = false;

	if (typeid(*command) == typeid(ResumeGame) ||
		typeid(*command) == typeid(RestartSession) ||
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
