#pragma once

#include <vector>
#include <string>

#include "MenuEntry.hpp"


struct Menu
{
	std::vector<MenuEntry> labels_;
	int32_t selected_;

public:
	void add_label(const std::string &label);
	void add_item(const std::string &label, ICommand *command);

	void scroll_down();
	void scroll_up();
	void scroll_left();
	void scroll_right();

	ICommand *select();
};
