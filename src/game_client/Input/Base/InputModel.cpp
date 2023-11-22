#include <sstream>
#include <fstream>
#include <iostream>

#include "InputModel.hpp"
#include "Command/Defines.hpp"


InputModel::InputModel(const std::string &config_path)
{
	std::ifstream file(config_path);

	if (!file.is_open())
	{
		clean_up();
		throw std::invalid_argument("Failed to open: " + config_path);
	}

	init_available_commands();
	parse_system_commands(file);
}

InputModel::~InputModel()
{
	clean_up();
}

void InputModel::clean_up()
{
	user_mapper_.clear();

	for (auto &[key, value]: available_commands_)
	{
		delete value.second;
		value.second = nullptr;
	}

	available_commands_.clear();
}

void InputModel::init_available_commands()
{
	// movement
	available_commands_["left"] = {false, new MovePlayer(LEFT)};
	available_commands_["right"] = {false, new MovePlayer(RIGHT)};
	available_commands_["up"] = {false, new MovePlayer(UP)};
	available_commands_["down"] = {false, new MovePlayer(DOWN)};

	// game states
	available_commands_["play"] = {false, new OpenPlayMenu};
	available_commands_["create"] = {false, new CreateSession};
	available_commands_["restart"] = {false, new RestartSession};
	available_commands_["pause"] = {false, new Pause};
	available_commands_["menu"] = {false, new OpenMainMenu};
	available_commands_["options"] = {false, new OpenGameOptions};
	available_commands_["resume"] = {false, new ResumeGame};
	available_commands_["terminate"] = {false, new Terminate};

	// menu
	available_commands_["scroll_down"] = {false, new ScrollDown};
	available_commands_["scroll_up"] = {false, new ScrollUp};
	available_commands_["scroll_left"] = {false, new ScrollLeft};
	available_commands_["scroll_right"] = {false, new ScrollRight};
	available_commands_["select"] = {false, new Select};

	// difficulty
	available_commands_["size_small"] = {false, new ChangeSize(SMALL)};
	available_commands_["size_medium"] = {false, new ChangeSize(MEDIUM)};
	available_commands_["size_big"] = {false, new ChangeSize(BIG)};
	available_commands_["difficulty_easy"] = {false, new ChangeDifficulty(EASY)};
	available_commands_["difficulty_average"] = {false, new ChangeDifficulty(AVERAGE)};
	available_commands_["difficulty_hard"] = {false, new ChangeDifficulty(HARD)};
}

void InputModel::parse_system_commands(std::ifstream &stream)
{
	std::string line;

	while (std::getline(stream, line))
	{
		parse_system_command(line);
	}

	if (user_mapper_.size() < 11)
	{
		clean_up();
		throw std::invalid_argument("Not enough keys to init");
	}
}

void InputModel::parse_system_command(const std::string &command)
{
	std::istringstream iss(command);
	std::string check_sum;
	int32_t key;

	iss >> check_sum >> key;

	if (available_commands_.find(check_sum) == available_commands_.end())
	{
		clean_up();
		throw std::invalid_argument("Invalid system command passed");
	}

	if (available_commands_.at(check_sum).first)
	{
		clean_up();
		throw std::invalid_argument("Key for command " + check_sum + " already exists");
	}

	if (user_mapper_.find(key) != user_mapper_.end())
	{
		const auto message = std::to_string(key) + " already bind on " + user_mapper_.at(key);
		clean_up();
		throw std::invalid_argument(message);
	}

	user_mapper_[key] = check_sum;
}

ICommand *InputModel::command(const std::string &key) const
{
	ICommand *ret = nullptr;

	if (available_commands_.find(key) != available_commands_.end())
	{
		ret = available_commands_.at(key).second;
	}

	return ret;
}

ICommand *InputModel::command(int32_t key) const
{
	ICommand *ret = nullptr;

	if (user_mapper_.find(key) != user_mapper_.end())
	{
		ret = command(user_mapper_.at(key));
	}

	return ret;
}

void InputModel::notify_subscribers(ICommand *command)
{
	for (auto &observer : observers_)
	{
		observer->update(command);
	}
}

void InputModel::add_subscriber(InputObserver *observer)
{
	if (observer == nullptr)
	{
		return;
	}

	observers_.push_back(observer);
}

void InputModel::remove_subscriber(InputObserver *observer)
{
	if (observer == nullptr)
	{
		return;
	}

	observers_.erase(std::find(observers_.begin(), observers_.end(), observer));
}
