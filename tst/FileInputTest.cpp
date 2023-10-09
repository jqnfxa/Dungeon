#include <Input/File/FileInput.hpp>
#include "gtest/gtest.h"

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
		EXPECT_TRUE(input.command() == nullptr);
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
		EXPECT_EQ(e.what(), std::string("Invalid system command passed"));
	}
}

TEST(FileInputSuite, TestButtonRedefinition)
{
	const std::string directory_path = "/home/shard/CLionProjects/DungeonGame/tst/";
	const std::string test = "test_3";

	try
	{
		FileInput input(directory_path + test);
	}
	catch (const std::invalid_argument &e)
	{
		EXPECT_EQ(e.what(), std::string("0 already bind on left"));
	}
}

TEST(FileInputSuite, TestButtonCommandsRedefinition)
{
	const std::string directory_path = "/home/shard/CLionProjects/DungeonGame/tst/";
	const std::string test = "test_4";

	try
	{
		FileInput input(directory_path + test);
	}
	catch (const std::invalid_argument &e)
	{
		EXPECT_EQ(e.what(), std::string("Key for command left already exists"));
	}
}

TEST(FileInputSuite, TestTooFewButtons)
{
	const std::string directory_path = "/home/shard/CLionProjects/DungeonGame/tst/";
	const std::string test = "test_5";

	try
	{
		FileInput input(directory_path + test);
	}
	catch (const std::invalid_argument &e)
	{
		EXPECT_EQ(e.what(), std::string("Not enough keys to init"));
	}
}