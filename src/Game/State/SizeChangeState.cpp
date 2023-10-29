#include "SizeChangeState.hpp"
#include "Command/System/TerminateProgram.hpp"
#include "Command/System/GameOptions.hpp"
#include "Command/Gameplay/ChangeFieldSize.hpp"

bool SizeChangeState::handle_command(GameEngine &game, Command *command)
{
	bool is_handled = false;
	if (typeid(*command) == typeid(TerminateProgram) || typeid(*command) == typeid(ChangeFieldSize)
	|| typeid(*command) == typeid(GameOptions))
	{
		command->execute(game);
		is_handled = true;
	}
	return is_handled;
}

std::string SizeChangeState::to_str() const
{
	return "SizeChangeState";
}
