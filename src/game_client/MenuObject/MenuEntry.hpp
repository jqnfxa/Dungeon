#pragma once

#include <vector>
#include <string>

#include "Command/ICommand.hpp"


struct MenuEntry
{
	std::string label;
	std::vector<ICommand *> options;
	int32_t selected;

	~MenuEntry();
	MenuEntry(std::string label, std::vector<ICommand *> options = {}, int32_t selected = 0);
	ICommand *get(int32_t idx) const;
};
