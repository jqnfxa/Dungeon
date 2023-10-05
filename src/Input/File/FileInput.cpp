#include "FileInput.hpp"
#include "Command/System/TerminateProgram.hpp"
#include "Command/System/NOP.hpp"
#include "Command/Gameplay/MovePlayer.hpp"
#include "Command/System/TriggerHoldMenu.hpp"
#include "Command/System/GoToSettings.hpp"
#include "Command/System/ReturnToMenu.hpp"
#include "Command/Gameplay/ChangeGameSize.hpp"
#include "Command/Gameplay/ChangeGameDifficulty.hpp"
#include "Command/Gameplay/CreateSession.hpp"
#include "Command/Gameplay/RestartSession.hpp"
#include <sstream>

FileInput::FileInput(const std::string &file) : file_(file), last_command_(nullptr), inited_(false)
{
	if (!file_.is_open())
	{
		throw std::invalid_argument("Failed to open: " + file);
	}

	file_.seekg(0);
}

Command *FileInput::convert_command(const std::string &command)
{
	if (available_commands_.find(command) == available_commands_.end())
	{
		return available_commands_["NOP"];
	}

	return available_commands_[command];
}

Command *FileInput::command()
{
	if (!inited_)
	{
		throw std::invalid_argument("Called to not inited class");
	}
	if (last_command_ == nullptr)
	{
		last_command_ = available_commands_["NOP"];
	}
	return last_command_;
}

void FileInput::update()
{
	if (!inited_)
	{
		throw std::invalid_argument("Called to not inited class");
	}
	std::string command;
	std::getline(file_, command);
	last_command_ = convert_command(command);
}

void FileInput::init()
{
	if (inited_)
	{
		return;
	}
	// data format
	// bind <button> (left | right | up | down)
	// size (small | medium | big)
	// difficulty (easy | medium | hard)

	for (int i = 0; i < 6; ++i)
	{
		std::string argument;
		std::getline(file_, argument);
		parse_as_system_command(argument);
	}

	if (available_commands_.find("SIZE") == available_commands_.end()
		|| available_commands_.find("DIFFICULTY") == available_commands_.end())
	{
		throw std::invalid_argument("Failed to associate map characteristics");
	}

	int check_sum = 0;
	for (auto &[key, value] : available_commands_)
	{
		if (value == MovePlayer(LEFT)
			|| value == MovePlayer(RIGHT)
			|| value == MovePlayer(UP)
			|| value == MovePlayer(DOWN))
		{
			check_sum++;
		}
	}
	if (available_commands_.find("left") == available_commands_.end()
		|| available_commands_.find("right") == available_commands_.end()
		|| available_commands_.find("up") == available_commands_.end()
		|| available_commands_.find("down") == available_commands_.end()
		|| available_commands_.find("SIZE") == available_commands_.end()
		|| available_commands_.find("DIFFICULTY") == available_commands_.end())
	{
		throw std::invalid_argument("Failed to associate buttons with commands");
	}

	available_commands_["NOP"] = new NOP;
	available_commands_["TERMINATE"] = new TerminateProgram;
	available_commands_["HOLD"] = new TriggerHoldMenu;
	available_commands_["SETTINGS"] = new GoToSettings;
	available_commands_["MENU"] = new ReturnToMenu;
	available_commands_["RUN"] = new CreateSession;
	available_commands_["RESTART"] = new RestartSession;

	inited_ = true;
}
FileInput::~FileInput()
{
	for (auto &[key, value]: available_commands_)
	{
		delete value;
	}
}
void FileInput::parse_as_system_command(const std::string &input_command)
{
	std::stringstream ss(input_command);

	std::string check_sum;
	ss >> check_sum;

	if (check_sum == "bind")
	{
		bind_keys(input_command);
	}
	else if (check_sum == "size")
	{
		update_size(input_command);
	}
	else if (check_sum == "difficulty")
	{
		update_difficulty(input_command);
	}
	else
	{
		throw std::invalid_argument("Unexpected system command: " + check_sum);
	}
}

void FileInput::bind_keys(const std::string &input_command)
{
	std::stringstream ss(input_command);

	std::string check_sum;
	ss >> check_sum;

	if (check_sum != "bind")
	{
		return;
	}

	char button;
	std::string command;

	ss.ignore(static_cast<int>(input_command.size()), ' ');
	ss >> button;
	ss >> command;
	std::string button_key = std::string(1, button);

	DIRECTION direction;

	if (command == "left")
	{
		direction = DIRECTION::LEFT;
	}
	else if (command == "right")
	{
		direction = DIRECTION::RIGHT;
	}
	else if (command == "up")
	{
		direction = DIRECTION::UP;
	}
	else if (command == "down")
	{
		direction = DIRECTION::DOWN;
	}
	else
	{
		throw std::invalid_argument("Invalid command passed: " + command);
	}

	if (available_commands_.find(button_key) != available_commands_.end())
	{
		throw std::invalid_argument("Button already was bind");
	}

	available_commands_[button_key] = new MovePlayer(direction);

	for (auto &[key, value]: available_commands_)
	{
		if (key != button_key && available_commands_[button_key]->operator==(value))
		{
			throw std::invalid_argument("Multiply buttons for command: " + command);
		}
	}

	available_commands_[command] = new MovePlayer(direction);
}

void FileInput::update_size(const std::string &input_command)
{
	std::stringstream ss(input_command);

	std::string check_sum;
	ss >> check_sum;

	if (check_sum != "size")
	{
		return;
	}

	std::string size;

	ss >> size;

	if (size != "small" && size != "medium" && size != "big")
	{
		throw std::invalid_argument("Bad size: " + size);
	}
	if (available_commands_.find("SIZE") != available_commands_.end())
	{
		delete available_commands_["SIZE"];
	}

	MAP_SIZE real_size;

	if (size == "small")
	{
		real_size = MAP_SIZE::SMALL;
	}
	else if (size == "medium")
	{
		real_size = MAP_SIZE::MEDIUM;
	}
	else if (size == "big")
	{
		real_size = MAP_SIZE::BIG;
	}

	available_commands_["SIZE"] = new ChangeGameSize(real_size);
}

void FileInput::update_difficulty(const std::string &input_command)
{
	std::stringstream ss(input_command);

	std::string check_sum;
	ss >> check_sum;

	if (check_sum != "difficulty")
	{
		return;
	}

	std::string difficulty;

	ss >> difficulty;

	if (difficulty != "easy" && difficulty != "medium" && difficulty != "hard")
	{
		throw std::invalid_argument("Bad difficulty: " + difficulty);
	}

	if (available_commands_.find("DIFFICULTY") != available_commands_.end())
	{
		delete available_commands_["DIFFICULTY"];
	}

	DIFFICULTY real_difficulty;

	if (difficulty == "easy")
	{
		real_difficulty = DIFFICULTY::EASY;
	}
	else if (difficulty == "medium")
	{
		real_difficulty = DIFFICULTY::AVERAGE;
	}
	else if (difficulty == "hard")
	{
		real_difficulty = DIFFICULTY::HARD;
	}

	available_commands_["DIFFICULTY"] = new ChangeGameDifficulty(real_difficulty);
}