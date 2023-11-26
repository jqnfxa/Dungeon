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

	if (processable.contains(typeid(*command)))
	{
		command->execute(engine);
		is_handled = true;
	}

	return is_handled;
}
