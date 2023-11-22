#pragma once

#include <unordered_map>
#include <vector>

#include "Command/ICommand.hpp"
#include "../InputObserver.hpp"


class InputModel {
private:
	std::vector<InputObserver *> observers_;

	void init_available_commands();
	void parse_system_command(const std::string &command);
	void parse_system_commands(std::ifstream &stream);

protected:

	std::unordered_map<std::string, std::pair<bool, ICommand *>> available_commands_;
	std::unordered_map<int32_t, std::string> user_mapper_;
	void clean_up();

public:

	explicit InputModel(const std::string &config_path);
	virtual ~InputModel();

	virtual void update() = 0;

	ICommand *last_command() const;
	ICommand *command(const std::string &key) const;
	ICommand *command(int32_t key) const;

	void notify_subscribers(ICommand *command);
	void add_subscriber(InputObserver *observer);
	void remove_subscriber(InputObserver *observer);
};
