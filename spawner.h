#pragma once

#include <vector>
#include "entity.h"
#include <utility>
#include <functional>

namespace adhart
{	
	struct spawner : public entity
	{
		enum state
		{
			EGG,
			SPAWNED,
			EMPTY
		};

		state current;
		entity* spawn;
		int speed;
		int tick;
		std::function<entity*()> kind;

		spawner(std::function<entity*()> kind)
			: current(state::EMPTY)
			, spawn(nullptr)
			, speed(rand() % 5 + 3)	// 3 to 8 turns
			, tick(0)
			, kind(kind)
		{}

		void clear()
		{
			current = state::EMPTY;
			spawn = nullptr;
		}

		void update()
		{
			if(current == EMPTY || current == EGG)
			{
				tick++;
				if(tick >= speed)
				{
					tick = 0;
					switch(current)
					{
						case EMPTY: 
							current = EGG; 
							break;
						case EGG:
							current = SPAWNED;
							spawn = kind();
							break;
					}
				}
			}
		}

		void draw()
		{
			switch(current)
			{
				case EMPTY:
					addch('=');
					break;
				case EGG:
					addch(tick % 2 == 0 ? 'o' : 'O');
					break;
				case SPAWNED:
					if(spawn != nullptr)
						spawn->draw();
					break;
			}
		}
	};
}
