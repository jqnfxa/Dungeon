#include <Event/Factory/EventFactory.hpp>
#include <Entities/Player/Player.hpp>
#include <Handlers/PlayerHandler/PlayerHandler.hpp>
#include "gtest/gtest.h"

TEST(EventFactorySuite, TestRandomMine)
{
	auto *map = new GameField;
	PlayerHandler handler(new Player);
	handler.register_observer(map);

	handler.set_position({5, 5});
	EventFactory::instance().reset_player_reference(&handler);
	auto *event = EventFactory::instance().create(EVENT_TYPE::RANDOM_MINE);

	auto previous = handler.get_position();
	event->trigger();
	EXPECT_FALSE(previous == handler.get_position());

	delete event;
	delete map;
}

TEST(EventFactorySuite, TestSpikes)
{
	PlayerHandler handler(new Player(100, 30));
	EventFactory::instance().reset_player_reference(&handler);
	auto *event = EventFactory::instance().create(EVENT_TYPE::SPIKES);

	EXPECT_EQ(handler.get_health(), 100);
	EXPECT_EQ(handler.get_armor(), 30);
	event->trigger();
	EXPECT_EQ(handler.get_health(), 100);
	EXPECT_EQ(handler.get_armor(), 15);
	event->trigger();
	EXPECT_EQ(handler.get_health(), 100);
	EXPECT_EQ(handler.get_armor(), 7);
	event->trigger();
	EXPECT_EQ(handler.get_health(), 80);
	EXPECT_EQ(handler.get_armor(), 7);

	handler.set_health(0);
	event->trigger();
	EXPECT_EQ(handler.get_health(), 0);

	delete event;
}

TEST(EventFactorySuite, TestStar)
{
	PlayerHandler handler(new Player);
	EventFactory::instance().reset_player_reference(&handler);
	auto *event = EventFactory::instance().create(EVENT_TYPE::STAR);

	EXPECT_EQ(handler.get_points(), 0);
	event->trigger();
	EXPECT_EQ(handler.get_points(), 100);

	handler.set_points(100000);
	EXPECT_EQ(handler.get_points(), 100000);
	event->trigger();
	EXPECT_EQ(handler.get_points(), 100000);

	delete event;
}

TEST(EventFactorySuite, TestShieldKit)
{
	PlayerHandler handler(new Player);
	EventFactory::instance().reset_player_reference(&handler);
	auto *event = EventFactory::instance().create(EVENT_TYPE::SHIELD_KIT);

	EXPECT_EQ(handler.get_armor(), 0);
	event->trigger();
	EXPECT_EQ(handler.get_armor(), 50);
	event->trigger();
	EXPECT_EQ(handler.get_points(), 0);
	event->trigger();
	EXPECT_EQ(handler.get_points(), 0);

	delete event;
}

TEST(EventFactorySuite, TestPotion)
{
	PlayerHandler handler(new Player);
	EventFactory::instance().reset_player_reference(&handler);
	auto *event = EventFactory::instance().create(EVENT_TYPE::POTION);

	EXPECT_EQ(handler.get_health(), 100);
	EXPECT_EQ(handler.get_attack(), 10);
	event->trigger();
	EXPECT_EQ(handler.get_health(), 100 + (1) * 50);
	EXPECT_EQ(handler.get_attack(), 10 + (1) * 10);
	delete event;
}