#pragma once

#include <istream>
#include <fstream>
#include <unordered_map>
#include "Command/Interface/Interface.hpp"
#include "Input/Base/InputClass.hpp"
#include "Movement/Direction.hpp"
#include "MapGenerator/DefaultLevels/DefaultLevelGenerator.hpp"

class FileInput : public Input {
  std::ifstream file_;
 public:
  explicit FileInput(const std::string &config_path);
  void process_file(const std::string &input);
  void update(GameState *game_state) override;
};
