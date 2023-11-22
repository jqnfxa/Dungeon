#pragma once

#include <istream>
#include <fstream>
#include <unordered_map>
#include "Input/Base/InputModel.hpp"


class FileInput : public InputModel {
	std::ifstream file_;
public:
	explicit FileInput(const std::string &config_path);

	void process_file(const std::string &input);
	void update() override;
};
