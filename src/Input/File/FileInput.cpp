#include <sstream>
#include "FileInput.hpp"
#include "Game/State/TerminateState.hpp"

FileInput::FileInput(const std::string &config_path) : Input(config_path)
{
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

void FileInput::update(GameState *game_state)
{
	if (game_state == nullptr)
	{
		return;
	}
	if (typeid(*game_state) != typeid(TerminateState))
	{
		last_command_ = nullptr;

		if (file_.is_open())
		{
			std::string command;
			file_ >> command;

			if (command == "difficulty" || command == "size")
			{
				std::string arg;
				file_ >> arg;
				last_command_ = available_commands_.at(command + "_" + arg).second;
			}
			else
			{
				int32_t key = std::stoi(command);

				if (user_mapper_.find(key) != user_mapper_.end())
				{
					last_command_ = available_commands_.at(user_mapper_.at(key)).second;
				}
			}
		}
	}
}