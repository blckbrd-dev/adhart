#pragma once

#include "entity.h"

namespace adhart 
{
	struct character : public entity
	{
		choice decision;
		entity* killer;
		int floor;
		int lvl;

		character() 
			: entity("player", 1, 10)
			, decision(NONE)
			, killer(nullptr)
			, floor(0)
			, lvl(1)
		{}

		~character()
		{}

		void update()
		{
			switch(decision)
			{
				case LEFT:
					if(alive)
						floor = level::current->walk(-1);
					break;
				case RIGHT:
					if(alive)
						floor = level::current->walk(1);
					break;
				case PRAY:
					// TODO: do something here
					break;
				case JUMP:
					// TODO: do something here
					break;
				case WAIT:
					break;
				case QUIT:
					exit(0);
					break;
			}

			decision = NONE;
		}

		void draw()
		{
			addch('@' | A_BOLD);
		}

		bool damage(entity* e)
		{
			if(entity::damage(e))
			{
				killer = e;
			}

			return !alive;
		}
	};
}