#pragma once

#include "IState.hpp"
#include "MenuObject/Menu.hpp"

#include "Command/Defines.hpp"
#include <unordered_set>
#include <typeindex>

class Play : public IState
{
	const std::unordered_set<std::type_index> processable = {
		typeid(MovePlayer),
		typeid(Pause),
		typeid(Terminate)
	};
public:
	Menu *menu() override;
	[[nodiscard]] bool handle_command(GameEngine &engine, ICommand* command) override;
};
