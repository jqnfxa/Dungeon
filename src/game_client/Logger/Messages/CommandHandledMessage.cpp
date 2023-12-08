#include "CommandHandledMessage.hpp"
#include "Command/Defines.hpp"
#include <sstream>
#include <unordered_map>
#include <typeindex>
#include <string>


const std::unordered_map<std::type_index, std::string> commands_aliases = {
	{typeid(ChangeDifficulty), "change difficulty"},
	{typeid(ChangeSize), "change size"},
	{typeid(CreateSession), "create a new session"},
	{typeid(MovePlayer), "move player"},
	{typeid(Pause), "pause"},
	{typeid(RestartSession), "restart"},
	{typeid(ResumeGame), "resume game"},
	{typeid(ScrollDown), "scroll down"},
	{typeid(ScrollUp), "scroll up"},
	{typeid(ScrollLeft), "scroll left"},
	{typeid(ScrollRight), "scroll right"},
	{typeid(Select), "select"},
	{typeid(OpenGameOptions), "open game options"},
	{typeid(OpenMainMenu), "open main menu"},
	{typeid(OpenPlayMenu), "open play menu"},
	{typeid(SwitchToLose), "switch to lose screen"},
	{typeid(SwitchToWin), "switch to win screen"},
	{typeid(Terminate), "terminate"}
};

CommandHandledMessage::CommandHandledMessage(ICommand *command) : command_(command)
{
	if (command_ == nullptr)
	{
		throw std::invalid_argument("Passed none command in command handled message");
	}
}

std::string CommandHandledMessage::to_string() const
{
	std::ostringstream oss;

	oss << "Command " << commands_aliases.at(typeid(*command_)) <<
	" was successfully executed.";

	return oss.str();
}
