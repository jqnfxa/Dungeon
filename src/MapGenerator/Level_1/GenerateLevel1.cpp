#include "GenerateLevel1.hpp"
#include "Event/RandomMine.hpp"
#include "Event/Spikes.hpp"
#include "Event/Potion.hpp"

#include <iostream>

GenerateLevel1::GenerateLevel1()
{}
Map GenerateLevel1::generate()
{
	Map map(10, 12);

	// start/end
	map.reset_start({1, 1});
	map.reset_finish({8, 9});

	// walls
	map.build_wall({0, 7});

	map.build_wall({1, 2});
	map.build_wall({1, 4});
	map.build_wall({1, 7});
	map.build_wall({1, 8});
	map.build_wall({1, 9});
	map.build_wall({1, 10});

	map.build_wall({2, 1});
	map.build_wall({2, 2});
	map.build_wall({2, 11});

	map.build_wall({3, 4});
	map.build_wall({3, 6});

	map.build_wall({4, 11});

	map.build_wall({5, 0});
	map.build_wall({5, 1});
	map.build_wall({5, 4});
	map.build_wall({5, 5});
	map.build_wall({5, 11});

	map.build_wall({6, 5});
	map.build_wall({6, 8});
	map.build_wall({6, 9});

	map.build_wall({7, 1});
	map.build_wall({7, 3});
	map.build_wall({7, 7});
	map.build_wall({7, 10});

	map.build_wall({8, 1});
	map.build_wall({8, 3});
	map.build_wall({8, 4});
	map.build_wall({8, 5});
	map.build_wall({8, 6});
	map.build_wall({8, 11});

	// events
	map.get_cell({0, 2}).add_event(new Spikes);
	map.get_cell({3, 0}).add_event(new Spikes);
	map.get_cell({3, 5}).add_event(new Spikes);
	map.get_cell({3, 8}).add_event(new Spikes);
	map.get_cell({5, 2}).add_event(new Spikes);
	map.get_cell({5, 3}).add_event(new Spikes);
	map.get_cell({5, 11}).add_event(new Spikes);
	map.get_cell({7, 5}).add_event(new Spikes);
	map.get_cell({9, 4}).add_event(new Spikes);
	map.get_cell({9, 7}).add_event(new Spikes);

	map.get_cell({0, 0}).add_event(new RandomMine);
	map.get_cell({3, 11}).add_event(new RandomMine);
	map.get_cell({6, 1}).add_event(new RandomMine);
	map.get_cell({9, 1}).add_event(new RandomMine);

	map.get_cell({6, 10}).add_event(new Potion);
	map.get_cell({0, 8}).add_event(new Potion);

	// add stat events
	Dimension dim = map.get_dimensions();

	for (int i = 0; i < dim.get_x(); ++i)
	{
		for (int j = 0; j < dim.get_y(); ++j)
		{
			char symbol;
			auto &cur_cell = map.get_cell({i, j});

			if (!cur_cell.is_movable())
			{
				symbol = '*';
			}
			if (cur_cell.is_movable())
			{
				symbol = ' ';
			}
			if (cur_cell.is_entrance())
			{
				symbol = '1';
			}
			if (cur_cell.is_exit())
			{
				symbol = '0';
			}
			if (cur_cell.get_active_event() != nullptr)
			{
				if (auto *e = dynamic_cast<const Spikes *>(cur_cell.get_active_event()); e != nullptr)
				{
					symbol = '#';
				}
				else if (auto *k = dynamic_cast<const Potion *>(cur_cell.get_active_event()); k != nullptr)
				{
					symbol = '+';
				}
				else if (auto *b = dynamic_cast<const RandomMine *>(cur_cell.get_active_event()); b != nullptr)
				{
					symbol = '?';
				}
			}
			std::cerr << symbol;
		}
		std::cerr << '\n';
	}
	std::cerr << std::endl;

	return std::move(map);
}
