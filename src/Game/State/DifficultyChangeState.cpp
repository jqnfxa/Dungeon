#include "DifficultyChangeState.hpp"
#include "Command/System/TerminateProgram.hpp"
#include "Command/System/GameOptions.hpp"
#include "Command/Gameplay/ChangeGameDifficulty.hpp"

bool DifficultyChangeState::handle_command(GameEngine &game, Command *command)
{
	bool is_handled = false;
	if (typeid(*command) == typeid(TerminateProgram) || typeid(*command) == typeid(ChangeGameDifficulty)
		|| typeid(*command) == typeid(GameOptions))
	{
		command->execute(game);
		is_handled = true;
	}
	return is_handled;
}
std::string DifficultyChangeState::to_str() const
{
	return "DifficultyChangeState";
}
