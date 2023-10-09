#include "Game/Engine/GameEngine.hpp"
#include "gtest/gtest.h"
#include "Input/File/FileInput.hpp"
#include "Game/State/MainMenuState.hpp"
#include "Game/State/PlayingState.hpp"
#include "Game/State/TerinateState.hpp"

TEST(GameEngineSuite, TestSimpleInteracting)
{
	const std::string directory_path = "/home/shard/CLionProjects/DungeonGame/tst/";
	const std::string test = "binds";
	const std::string actions = "test_game_engine_1";

	GameEngine game;

	EXPECT_FALSE(dynamic_cast<MainMenuState *>(game.state()) == nullptr);

	FileInput input(directory_path + test);
	input.process_file(directory_path + actions);

	do
	{
		input.update();
		game.update(input.command());

		if (dynamic_cast<PlayingState *>(game.state()))
		{
			//game.field()->print(std::cerr);
			std::cerr << game.player()->get_position().x() << ' ' << game.player()->get_position().y() << std::endl;
		}
		std::cerr << game.state()->to_str() << std::endl;
	} while (dynamic_cast<TerminateState *>(game.state()) == nullptr);
}