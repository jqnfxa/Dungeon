#pragma once

#include <istream>
#include <fstream>
#include <unordered_map>
#include "Command/Interface/Interface.hpp"
#include "Input/Interface/InputClass.hpp"
#include "Movement/Direction.hpp"

class FileInput : public Input {
  std::ifstream file_;
  Command *last_command_;
  bool inited_;

  std::unordered_map<std::string, Command *> available_commands_;
  Command *convert_command(const std::string &command);
  void parse_as_system_command(const std::string &input_command);
  void bind_keys(const std::string &input_command);
  void update_size(const std::string &input_command);
  void update_difficulty(const std::string &input_command);
 public:
  explicit FileInput(const std::string &file);
  ~FileInput() override;
  void init();
  Command* command() override;
  void update() override;
};
