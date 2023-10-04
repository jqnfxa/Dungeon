#include "FileInput.hpp"
#include "Command/System/TerminateProgram.hpp"
#include "Command/System/NOP.hpp"
#include "Command/Movement/MovePlayer.hpp"
#include "Command/System/TriggerHoldMenu.hpp"
#include "Command/System/GoToSettings.hpp"
#include "Command/System/ReturnToMenu.hpp"
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
	// bind <button> <command>

	std::string str;

	for (int i = 0; file_.good() && i < 4; ++i)
	{
		std::getline(file_, str);
		std::stringstream ss(str);

		char button;
		std::string check_sum, command;

		ss >> check_sum;
		ss.ignore(static_cast<int>(str.size()), ' ');
		ss >> button;
		ss >> command;

		std::string button_key = std::string(1, button);

		if (check_sum != "bind")
		{
			throw std::invalid_argument("Unexpected initial command: " + check_sum);
		}

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

		for (auto &[key, value] : available_commands_)
		{
			if (key != button_key && value == available_commands_[button_key])
			{
				throw std::invalid_argument("Multiply buttons for command: " + command);
			}
		}
	}

	if (available_commands_.size() < 4)
	{
		throw std::invalid_argument("Failed to associate buttons with commands");
	}

	available_commands_["NOP"] = new NOP;
	available_commands_["TERMINATE"] = new TerminateProgram;
	available_commands_["HOLD"] = new TriggerHoldMenu;
	available_commands_["SETTINGS"] = new GoToSettings;
	available_commands_["MENU"] = new ReturnToMenu;

	inited_ = true;
}
FileInput::~FileInput()
{
	for (auto &[key, value] : available_commands_)
	{
		delete value;
	}
}