#pragma once

#include "IState.hpp"
#include "MenuObject/Menu.hpp"

#include "Command/Defines.hpp"
#include <unordered_set>
#include <typeindex>

class HoldState : public IState
{
	Menu menu_;

	const std::unordered_set<std::type_index> processable = {
		typeid(ResumeGame),
		typeid(RestartSession),
		typeid(OpenMainMenu),
		typeid(ScrollDown),
		typeid(ScrollUp),
		typeid(Select),
		typeid(Terminate)
	};
public:
	HoldState();
	Menu *menu() override;
	[[nodiscard]] bool handle_command(GameEngine &engine, ICommand* command) override;
};
