#include "MenuEntry.hpp"


MenuEntry::~MenuEntry()
{
	for (auto &option : options)
	{
		delete option;
	}

	options.clear();
}

MenuEntry::MenuEntry(std::string label, std::vector<ICommand *> options, int32_t selected)
	: label(std::move(label)), options(std::move(options)), selected(selected) {}

ICommand *MenuEntry::get(int32_t idx) const
{
	if (idx < 0 || idx >= options.size())
	{
		return nullptr;
	}

	return options[selected];
}
