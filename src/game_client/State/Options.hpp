#pragma once

#include "IState.hpp"
#include "MenuObject/Menu.hpp"

#include "Command/Defines.hpp"
#include <unordered_set>
#include <typeindex>

class Options : public IState
{
	Menu menu_;

	const std::unordered_set<std::type_index> processable = {
		typeid(SetupLoggerEmpty),
		typeid(SetupLoggerConsole),
		typeid(SetupLoggerFile),
		typeid(SetupLoggerBoth),
		typeid(ChangeSize),
		typeid(ChangeDifficulty),
		typeid(OpenMainMenu),
		typeid(ScrollDown),
		typeid(ScrollUp),
		typeid(ScrollLeft),
		typeid(ScrollRight),
		typeid(Select),
		typeid(Terminate)
	};
public:
	Options();
	Menu *menu() override;
	[[nodiscard]] bool handle_command(GameEngine &engine, ICommand* command) override;
};
