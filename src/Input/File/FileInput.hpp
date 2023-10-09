#pragma once

#include <istream>
#include <fstream>
#include <unordered_map>
#include "Command/Interface/Interface.hpp"
#include "Input/Interface/InputClass.hpp"
#include "Movement/Direction.hpp"
#include "MapGenerator/DefaultLevels/DefaultLevelGenerator.hpp"

class FileInput : public Input {
  Command *last_command_;
  std::ifstream file_;

  std::unordered_map<std::string, std::pair<bool, Command *>> available_commands_;
  std::unordered_map<int32_t, std::string> user_mapper_;

  void clean_up();
  void init_available_commands();
  void parse_system_command(const std::string &command);
  void parse_system_commands(std::ifstream &stream);
 public:
  explicit FileInput(const std::string &config);
  ~FileInput() override;

  void process_file(const std::string &input);
  Command* command() override;
  void update() override;
};
