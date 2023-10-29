#include "InputClass.hpp"
#include "Command/Include/Defines.hpp"
#include "Command/System/OpenSizeOptions.hpp"
#include "Command/System/OpenDifficultyOptions.hpp"
#include <sstream>
#include <fstream>

Input::Input(const std::string &config_path) : last_command_(nullptr)
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

Input::~Input()
{
	clean_up();
}

void Input::clean_up()
{
	user_mapper_.clear();
	for (auto &[key, value]: available_commands_)
	{
		delete value.second;
		value.second = nullptr;
	}
	available_commands_.clear();
}

void Input::init_available_commands()
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
	available_commands_["pause"] = {false, new OpenHoldMenu};
	available_commands_["menu"] = {false, new OpenMainMenu};
	available_commands_["options"] = {false, new GameOptions};
	available_commands_["resume"] = {false, new ResumeGame};
	available_commands_["terminate"] = {false, new TerminateProgram};
	available_commands_["size_state"] = {false, new OpenSizeOptions};
	available_commands_["difficulty_state"] = {false, new OpenDifficultyOptions};

	// difficulty
	available_commands_["size_small"] = {false, new ChangeFieldSize(SMALL)};
	available_commands_["size_medium"] = {false, new ChangeFieldSize(MEDIUM)};
	available_commands_["size_big"] = {false, new ChangeFieldSize(BIG)};
	available_commands_["difficulty_easy"] = {false, new ChangeGameDifficulty(EASY)};
	available_commands_["difficulty_average"] = {false, new ChangeGameDifficulty(AVERAGE)};
	available_commands_["difficulty_hard"] = {false, new ChangeGameDifficulty(HARD)};
}

void Input::parse_system_commands(std::ifstream &stream)
{
	std::string line;

	while (std::getline(stream, line))
	{
		parse_system_command(line);
	}

	if (user_mapper_.size() < 12)
	{
		clean_up();
		throw std::invalid_argument("Not enough keys to init");
	}
}

void Input::parse_system_command(const std::string &command)
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

Command *Input::last_command() const
{
	return last_command_;
}

Command *Input::command(const std::string &key) const
{
	Command *ret = nullptr;

	if (available_commands_.find(key) != available_commands_.end())
	{
		ret = available_commands_.at(key).second;
	}
	return ret;
}

Command *Input::command(int32_t key) const
{
	Command *ret = nullptr;

	if (user_mapper_.find(key) != user_mapper_.end())
	{
		ret = available_commands_.at(user_mapper_.at(key)).second;
	}
	return ret;
}
