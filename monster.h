#pragma once

#include "entity.h"
#include "level.h"
#include "choice.h"
#include "character.h"
#include "utility.h"
#include <string>

namespace adhart 
{
	struct monster : public entity 
	{
		bool hatched;
		char symbol;

		monster(std::string name, char symbol, int p , int t)
			: entity(name, p, t)
			, hatched(false)
			, symbol(symbol)
		{}

		void init()
		{
			hatched = true;
		}

		virtual void live() = 0;

		void update()
		{
			if(hatched)
			{
				live();
			}
		}

		void draw()
		{
			addch(symbol);
		}
	};

	struct kobold : public monster
	{
		kobold()
			: monster("kobold", 'k', 1, 1)
		{}

		void live()
		{
			auto char_at = level::current->find<character>().first;
			if(char_at != -1)
			{
				auto this_at = level::iterator;
				level::current->walk(sgn(char_at - this_at));
			}
		}
	};

	struct ogre : public monster
	{
		bool rest;

		ogre()
			: monster("ogre", 'G', 3, 1)
			, rest(true)
		{}

		void live()
		{
			rest = !rest;

			if(!rest) {
				auto char_at = level::current->find<character>().first;
				if(char_at != -1)
				{
					auto this_at = level::iterator;
					level::current->walk(sgn(char_at - this_at));
				}
			}
		}
	};
}
