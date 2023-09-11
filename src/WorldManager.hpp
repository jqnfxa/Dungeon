#pragma once
#include <vector>
#include "Entities/Player.hpp"
#include "Entities/Bot.hpp"

enum Direction
{
	none,
	left_up,
	up,
	right_up,
	right,
	right_bottom,
	down,
	left_down,
	left
};

const std::vector<std::vector<int32_t>> moves = {{0,0},{-1,-1},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1}};

class WorldManager {
 private:
  Player player_;
 public:
  WorldManager(uint32_t dim_x, uint32_t dim_y);
  void move_player(const Direction &direction);
};
