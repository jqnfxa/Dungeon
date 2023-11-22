#include "DefaultLevelGenerator.hpp"

DefaultLevelGenerator::DefaultLevelGenerator(MAP_SIZE size, DIFFICULTY difficulty) : size_(size), difficulty_(difficulty)
{
}

GameField *DefaultLevelGenerator::generate() const
{
	Dimension field_dimensions;
	int32_t events_percent;
	int32_t positive_events;
	int32_t negative_events;
	int32_t other_events;

	switch (size_)
	{
		case MEDIUM:
			field_dimensions.set_x(25);
			field_dimensions.set_y(30);
			break;
		case BIG:
			field_dimensions.set_x(100);
			field_dimensions.set_y(100);
			break;
		case HUGE:
			field_dimensions.set_x(300);
			field_dimensions.set_y(300);
			break;
		case SMALL:
		default:
			field_dimensions.set_x(10);
			field_dimensions.set_y(10);
			break;
	}

	switch (difficulty_)
	{
		case AVERAGE:
			events_percent = 40;
			positive_events = 30;
			negative_events = 30;
			other_events = 30;
			break;
		case HARD:
			events_percent = 60;
			positive_events = 10;
			negative_events = 70;
			other_events = 20;
			break;
		case EASY:
		default:
			events_percent = 30;
			positive_events = 60;
			negative_events = 20;
			other_events = 10;
			break;
	}
	Generator gen(field_dimensions.x(), field_dimensions.y(), events_percent, positive_events, negative_events, other_events);
	return gen.generate();
}
