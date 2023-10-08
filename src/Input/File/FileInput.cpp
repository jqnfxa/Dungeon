#include "FileInput.hpp"
#include "Command/Include/Defines.hpp"
#include <sstream>

FileInput::FileInput(const std::string &binds) : last_command_(nullptr)
{
	std::ifstream file(binds);

	if (!file.is_open())
	{
		clean_up();
		throw std::invalid_argument("Failed to open: " + binds);
	}

	parse_system_commands(file);
	last_command_ = available_commands_["NOP"];
}

Command *FileInput::command()
{
	return last_command_;
}

void FileInput::update()
{
	last_command_ = available_commands_["NOP"];

	if (file_.is_open())
	{
		std::string command;
		std::getline(file_, command);

		if (available_commands_.find(command) != available_commands_.end())
		{
			last_command_ = available_commands_[command];
		}
	}
}

FileInput::~FileInput()
{
	clean_up();
}

void FileInput::bind_keys(const std::string &input_command)
{
	std::stringstream ss(input_command);

	std::string check_sum;
	ss >> check_sum;

	if (check_sum != "key")
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
		clean_up();
		throw std::invalid_argument("Invalid command passed: " + command);
	}

	if (available_commands_.find(button_key) != available_commands_.end())
	{
		clean_up();
		throw std::invalid_argument("Button already was bind");
	}

	available_commands_[button_key] = new MovePlayer(direction);

	for (auto &[key, value]: available_commands_)
	{
		if (key != button_key && available_commands_[button_key]->operator==(value))
		{
			clean_up();
			throw std::invalid_argument("Multiple buttons for command: " + command);
		}
	}
}

void FileInput::read_simple_command(const std::string &string)
{
	std::stringstream ss(string);

	std::string check_sum, key;
	ss >> check_sum >> key;

	if (available_commands_.find(check_sum) != available_commands_.end())
	{
		clean_up();
		throw std::invalid_argument(check_sum + " already was bind");
	}

	if (check_sum == "create")
	{
		available_commands_[key] = new CreateSession;
	}
	else if (check_sum == "restart")
	{
		available_commands_[key] = new RestartSession;
	}
	else if (check_sum == "resume")
	{
		available_commands_[key] = new ResumeGame;
	}
	else if (check_sum == "hold")
	{
		available_commands_[key] = new OpenHoldMenu;
	}
	else if (check_sum == "main")
	{
		available_commands_[key] = new ReturnToMenu;
	}
	else if (check_sum == "terminate")
	{
		available_commands_[key] = new TerminateProgram;
	}
	else if (check_sum == "play")
	{
		available_commands_[key] = new OpenPlayMenu;
	}
	else if (check_sum == "size")
	{
		available_commands_["size"] = new ChangeFieldSize(parse_size(key));
	}
	else if (check_sum == "difficulty")
	{
		available_commands_["difficulty"] = new ChangeGameDifficulty(parse_difficulty(key));
	}
}

MAP_SIZE FileInput::parse_size(const std::string &string)
{
	if (string == "medium")
	{
		return MEDIUM;
	}
	else if (string == "big")
	{
		return BIG;
	}
	return SMALL;
}

DIFFICULTY FileInput::parse_difficulty(const std::string &string)
{
	if (string == "medium")
	{
		return AVERAGE;
	}
	else if (string == "hard")
	{
		return HARD;
	}
	return EASY;
}

void FileInput::parse_system_commands(std::ifstream &stream)
{
	std::string line;

	int keys = 0, other = 0;
	while (std::getline(stream, line))
	{
		if (line.find("key") != std::string::npos)
		{
			keys++;
			bind_keys(line);
		}
		else
		{
			other++;
			read_simple_command(line);
		}
	}
	if (keys < 4)
	{
		clean_up();
		throw std::invalid_argument("Too few keys for movement");
	}
	if (other < 9)
	{
		clean_up();
		throw std::invalid_argument("Too few buttons passed");
	}

	available_commands_["NOP"] = new NOP;
}

void FileInput::process_file(const std::string &input)
{
	file_.open(input);

	if (!file_.is_open())
	{
		clean_up();
		throw std::invalid_argument("Failed to open " + input);
	}
}

void FileInput::clean_up()
{
	for (auto &[key, value]: available_commands_)
	{
		delete value;
		value = nullptr;
	}
	available_commands_.clear();
}