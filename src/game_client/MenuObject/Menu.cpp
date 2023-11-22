#include <algorithm>
#include "Menu.hpp"


void Menu::add_label(const std::string &label)
{
	const auto equal = [&label] (const auto &item) { return item.label == label; };

	if (std::find_if(labels_.begin(), labels_.end(), equal) == labels_.end())
	{
		labels_.emplace_back(label);
	}
}

void Menu::add_item(const std::string &label, ICommand *command)
{
	if (command == nullptr)
	{
		return;
	}

	const auto equal = [&label] (const auto &item) { return item.label == label; };
	auto it = std::find_if(labels_.begin(), labels_.end(), equal);

	if (it != labels_.end())
	{
		it->options.push_back(command);
	}
}

void Menu::scroll_down()
{
	if (selected_ + 1 < labels_.size())
	{
		++selected_;
	}
}

void Menu::scroll_up()
{
	if (selected_ >= 1)
	{
		--selected_;
	}
}

void Menu::scroll_left()
{
	if (labels_[selected_].selected >= 1)
	{
		--labels_[selected_].selected;
	}
}

void Menu::scroll_right()
{
	if (labels_[selected_].selected + 1 < labels_[selected_].options.size())
	{
		++labels_[selected_].selected;
	}
}

ICommand *Menu::select()
{
	return labels_[selected_].get(labels_[selected_].selected);
}
