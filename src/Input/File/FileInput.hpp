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

  std::unordered_map<std::string, Command *> available_commands_;

  void clean_up();
  void bind_keys(const std::string &string);
  void read_simple_command(const std::string &string);
  MAP_SIZE parse_size(const std::string &string);
  DIFFICULTY parse_difficulty(const std::string &string);
  void parse_system_commands(std::ifstream &stream);
 public:
  explicit FileInput(const std::string &binds);
  ~FileInput() override;
  void process_file(const std::string &input);
  Command* command() override;
  void update() override;
};
