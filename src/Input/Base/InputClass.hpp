#pragma once

#include <unordered_map>
#include "Command/Interface/Interface.hpp"
#include "Game/State/GameState.hpp"

class Input {
 private:
  void init_available_commands();
  void parse_system_command(const std::string &command);
  void parse_system_commands(std::ifstream &stream);
 protected:
  Command *last_command_;
  std::unordered_map<std::string, std::pair<bool, Command *>> available_commands_;
  std::unordered_map<int32_t, std::string> user_mapper_;
  void clean_up();
 public:
  explicit Input(const std::string &config_path);
  virtual ~Input();
  virtual void update(GameState *game_state) = 0;
  Command *last_command() const;
  Command *command(const std::string &key) const;
  Command *command(int32_t key) const;
};