#include <Input/File/FileInput.hpp>
#include "gtest/gtest.h"
#include "Command/System/NOP.hpp"

TEST(FileInputSuite, TestNoFile)
{
	const std::string test = "not a file name";
	try
	{
		FileInput input(test);

		FAIL();
	}
	catch (const std::invalid_argument &e)
	{
		EXPECT_EQ(e.what(), "Failed to open: " + test);
	}
}

TEST(FileInputSuite, TestValidCreation)
{
	const std::string directory_path = "/home/shard/CLionProjects/DungeonGame/tst/";
	const std::string test = "binds";

	try
	{
		FileInput input(directory_path + test);
		EXPECT_TRUE(dynamic_cast<NOP *>(input.command()) != nullptr);
	}
	catch (...)
	{
		FAIL();
	}
}

TEST(FileInputSuite, TestWrongSequence)
{
	const std::string directory_path = "/home/shard/CLionProjects/DungeonGame/tst/";
	const std::string test = "test_2";

	try
	{
		FileInput input(directory_path + test);
	}
	catch (const std::invalid_argument &e)
	{
		EXPECT_EQ(e.what(), std::string("Too few keys for movement"));
	}
}

TEST(FileInputSuite, TestWrongDirection)
{
	const std::string directory_path = "/home/shard/CLionProjects/DungeonGame/tst/";
	const std::string test = "test_3";

	try
	{
		FileInput input(directory_path + test);
	}
	catch (const std::invalid_argument &e)
	{
		EXPECT_EQ(e.what(), std::string("Invalid command passed: ") + "upside");
	}
}

TEST(FileInputSuite, TestButtonRedefinition)
{
	const std::string directory_path = "/home/shard/CLionProjects/DungeonGame/tst/";
	const std::string test = "test_4";

	try
	{
		FileInput input(directory_path + test);
	}
	catch (const std::invalid_argument &e)
	{
		EXPECT_EQ(e.what(), std::string("Button already was bind"));
	}
}

TEST(FileInputSuite, TestButtonCommandsRedefinition)
{
	const std::string directory_path = "/home/shard/CLionProjects/DungeonGame/tst/";
	const std::string test = "test_5";

	try
	{
		FileInput input(directory_path + test);
	}
	catch (const std::invalid_argument &e)
	{
		EXPECT_EQ(e.what(), std::string("Multiple buttons for command: ") + "left");
	}
}

TEST(FileInputSuite, TestTooFewButtons)
{
	const std::string directory_path = "/home/shard/CLionProjects/DungeonGame/tst/";
	const std::string test = "test_6";

	try
	{
		FileInput input(directory_path + test);
	}
	catch (const std::invalid_argument &e)
	{
		EXPECT_EQ(e.what(), std::string("Too few buttons passed"));
	}
}