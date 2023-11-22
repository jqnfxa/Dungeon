#include "Play.hpp"
#include "Command/Defines.hpp"

Menu *Play::menu()
{
	return nullptr;
}

bool Play::handle_command(GameEngine &engine, ICommand *command)
{
	if (command == nullptr)
	{
		return false;
	}

	bool is_handled = false;

	if (typeid(*command) == typeid(MovePlayer) ||
		typeid(*command) == typeid(Pause) ||
		typeid(*command) == typeid(Terminate))
	{
		command->execute(engine);
		is_handled = true;
	}

	return is_handled;
}
