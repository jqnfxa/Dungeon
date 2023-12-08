#include "MainMenu.hpp"
#include "Command/Defines.hpp"


MainMenuState::MainMenuState() : menu_()
{
	menu_.add_label("play");
	menu_.add_label("settings");
	menu_.add_label("exit");

	menu_.add_item("play", new OpenPlayMenu);
	menu_.add_item("settings", new OpenGameOptions);
	menu_.add_item("exit", new Terminate);
}

Menu *MainMenuState::menu()
{
	return &menu_;
}

bool MainMenuState::handle_command(GameEngine &engine, ICommand *command)
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