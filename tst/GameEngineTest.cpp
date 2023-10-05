#include <Game/GameEngine.hpp>
#include "gtest/gtest.h"
#include "Input/File/FileInput.hpp"

TEST(GameEngineSuite, TestLevelStart)
{
	const std::string directory_path = "/home/shard/CLionProjects/DungeonGame/tst/";
	const std::string test = "test_game_engine_1";

	GameEngine game;

	EXPECT_EQ(game.state().active(), GameState::MAIN_MENU);

	FileInput input(directory_path + test);
	input.init();

	do
	{
		input.update();
		game.update(input.command());

		if (game.state() != GameState::TERMINATE)
		{
			game.field()->print(std::cerr);
			std::cerr << game.player()->get_position().x() << ' ' << game.player()->get_position().y() << std::endl;
		}
	} while (game.state() != GameState::TERMINATE);
}