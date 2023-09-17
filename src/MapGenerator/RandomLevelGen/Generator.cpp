#include "Generator.hpp"
#include "Event/Potion.hpp"
#include "Event/RandomMine.hpp"
#include "Event/Spikes.hpp"
#include "Random/Random.hpp"
#include <set>
#include <random>
#include <stack>
#include <iostream>

Map *Generator::generate() const
{
	auto engine = Random::get_instance();

	Position start(engine.pick_num(0, m_ / 4 - 1), engine.pick_num(0, n_ - 1));
	Position finish(engine.pick_num(m_ * 3 / 4, m_ - 1), engine.pick_num(0, n_ - 1));

	Map *map = new Map(m_, n_);

	map->reset_start(start);
	map->reset_finish(finish);

	for (int32_t i = 0; i < map->get_dimensions().get_x(); ++i)
	{
		for (int32_t j = 0; j < map->get_dimensions().get_y(); ++j)
		{
			auto &cell = map->get_cell({i, j});
			if (cell.is_exit() || cell.is_entrance())
			{
				continue;
			}
			cell.set_type(Cell::Type::wall);
		}
	}

	Position current = start;

	std::set<Position> visited;
	std::stack<Position> path;
	visited.insert(current);

	while (current != finish)
	{
		auto &cur_cell = map->get_cell(current);

		if (!cur_cell.is_entrance() & !cur_cell.is_exit())
		{
			cur_cell.set_type(Cell::Type::movable);
		}

		Position next;
		bool found_unvisited = false;

		for (int32_t i = 0; i < random_tries_limit; ++i)
		{
			next = Direction::getInstance().calculate_position(current, engine.pick_direction());

			if (map->is_on_map(next) && visited.count(next) == 0)
			{
				found_unvisited = true;
				break;
			}
		}

		if (!found_unvisited)
		{
			for (int32_t i = 2; i <= 8; i += 2)
			{
				next = Direction::getInstance().calculate_position(current, static_cast<DIRECTION>(i));
				if (map->is_on_map(next) && visited.count(next) == 0)
				{
					found_unvisited = true;
					break;
				}
			}
		}

		if (found_unvisited)
		{
			current = next;
			visited.insert(current);
			path.push(current);
		}
		else if (!path.empty())
		{
			path.pop();

			if (!path.empty())
			{
				current = path.top();
			}
		}
	}

	int32_t closed_cells_now = 0;
	for (int32_t i = 0; i < map->get_dimensions().get_x(); ++i)
	{
		for (int32_t j = 0; j < map->get_dimensions().get_y(); ++j)
		{
			if (!map->get_cell({i, j}).is_movable())
			{
				closed_cells_now++;
			}
		}
	}

	while (closed_cells_now > closed_cells)
	{
		int32_t x = engine.pick_num(0, m_ - 1);
		int32_t y = engine.pick_num(0, n_ - 1);

		if (!map->get_cell({x, y}).is_movable() && map->is_adjacent_to_movable({x, y}))
		{
			map->get_cell({x, y}).set_type(Cell::Type::movable);
			closed_cells_now--;
		}
	}

	std::vector<Position> movable_cells;

	for (int32_t i = 0; i < map->get_dimensions().get_x(); i++)
	{
		for (int32_t j = 0; j < map->get_dimensions().get_y(); j++)
		{
			Position cur_point(i, j);
			if (cur_point == start || cur_point == finish)
			{
				continue;
			}
			if (!map->get_cell({i, j}).is_movable())
			{
				continue;
			}
			movable_cells.emplace_back(cur_point);
		}
	}

	std::shuffle(movable_cells.begin(), movable_cells.end(), std::mt19937(std::random_device()()));

	auto events = generate_events(std::min(static_cast<int32_t>(movable_cells.size()), num_potions_ + num_random_mines_ + num_spikes_));
	std::shuffle(events.begin(), events.end(), std::mt19937(std::random_device()()));

	for (int32_t i = 0; i < events.size(); ++i)
	{
		map->get_cell(movable_cells[i]).add_event(events[i]);
	}

	return map;
}
Generator::Generator(int32_t m, int32_t n, int32_t closed_cells_percent, int32_t total_events, int32_t positive_events_percent, int32_t negative_events_percent) : m_(m),
																																								   n_(n)
{
	// TODO what if positive_events_percent + negative_events_percent > 100 ?
	int32_t cells_available = m_ * n_ - 2;
	double other_event_percent = (1.0 - positive_events_percent / 100.0 - negative_events_percent / 100.0) * 100.0;

	closed_cells = static_cast<int32_t>(static_cast<double>(closed_cells_percent) / 100.0 * cells_available);

	total_events = std::min(cells_available - closed_cells - 1, total_events);
	total_events = std::max(0, total_events);

	num_potions_ = static_cast<int32_t>(total_events * 1.0 * positive_events_percent / 100.0);
	num_random_mines_ = static_cast<int32_t>(total_events * 1.0 * other_event_percent / 100.0);
	num_spikes_ = static_cast<int32_t>(total_events * 1.0 * negative_events_percent / 100.0);
}
std::vector<EventInterface *> Generator::generate_events(int32_t lim) const
{
	std::vector<EventInterface *> events;
	events.reserve(lim);

	int32_t num_spikes = num_spikes_;
	int32_t num_potions = num_potions_;
	int32_t num_random_mines = num_random_mines_;

	while(events.size() < lim)
	{
		if (events.size() < lim && num_spikes > 0)
		{
			events.push_back(new Spikes);
			num_spikes--;
		}
		if (events.size() < lim && num_potions > 0)
		{
			events.push_back(new Potion);
			num_potions--;
		}
		if (events.size() < lim && num_random_mines > 0)
		{
			events.push_back(new RandomMine);
			num_random_mines--;
		}
	}
	return events;
}
