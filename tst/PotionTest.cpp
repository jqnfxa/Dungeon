#include "Event/PositiveEvents/Potion.hpp"
#include <Entities/Player/Player.hpp>
#include <Handlers/PlayerHandler/PlayerHandler.hpp>
#include "gtest/gtest.h"
#include "Event/Factory/EventFactory.hpp"

TEST(TestPotionSuite, TestPotionInteraction)
{
	MapHandler map_handler(new GameField);
	PlayerHandler player_handler(new Player(100, 20), &map_handler);

	EXPECT_EQ(player_handler.get_health(), 100);
	EXPECT_EQ(player_handler.get_attack(), 10);

	EventInterface *event = EventFactory::instance().create(EVENT_TYPE::POTION);
	event->interaction(&player_handler);

	EXPECT_EQ(player_handler.get_health(), 150);
	EXPECT_EQ(player_handler.get_armor(), 20);

	player_handler.set_health(80);
	event->interaction(&player_handler);
	EXPECT_EQ(player_handler.get_health(), 130);

	delete event;
}