#include "Options.hpp"
#include "Command/Defines.hpp"


Options::Options() : menu_()
{
	menu_.add_label("size");
	menu_.add_label("difficulty");
	menu_.add_label("menu");

	menu_.add_item("size", new ChangeSize(MAP_SIZE::SMALL));
	menu_.add_item("size", new ChangeSize(MAP_SIZE::MEDIUM));
	menu_.add_item("size", new ChangeSize(MAP_SIZE::BIG));

	menu_.add_item("difficulty", new ChangeDifficulty(DIFFICULTY::EASY));
	menu_.add_item("difficulty", new ChangeDifficulty(DIFFICULTY::AVERAGE));
	menu_.add_item("difficulty", new ChangeDifficulty(DIFFICULTY::HARD));

	menu_.add_item("menu", new OpenMainMenu);
}

Menu *Options::menu()
{
	return &menu_;
}

bool Options::handle_command(GameEngine &engine, ICommand *command)
{
	if (command == nullptr)
	{
		return false;
	}

	bool is_handled = false;

	if (typeid(*command) == typeid(ChangeSize) ||
		typeid(*command) == typeid(ChangeDifficulty) ||
		typeid(*command) == typeid(OpenMainMenu) ||
		typeid(*command) == typeid(ScrollDown) ||
		typeid(*command) == typeid(ScrollUp) ||
		typeid(*command) == typeid(ScrollLeft) ||
		typeid(*command) == typeid(ScrollRight) ||
		typeid(*command) == typeid(Select) ||
		typeid(*command) == typeid(Terminate))
	{
		command->execute(engine);
		is_handled = true;
	}

	return is_handled;
}
