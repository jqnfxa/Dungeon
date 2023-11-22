#include <sstream>
#include "File.hpp"


FileInput::FileInput(const std::string &config_path) : InputModel(config_path) {}

void FileInput::process_file(const std::string &input)
{
	file_.open(input);

	if (!file_.is_open())
	{
		clean_up();
		throw std::invalid_argument("Failed to open " + input);
	}
}

void FileInput::update()
{
	if (file_.is_open())
	{
		int32_t user_command;
		file_ >> user_command;

		notify_subscribers(command(user_command));
	}
}
