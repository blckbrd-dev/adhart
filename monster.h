#pragma once

#include "entity.h"
#include "level.h"
#include "choice.h"
#include "character.h"
#include "utility.h"

namespace adhart 
{
	struct monster : public entity 
	{
		bool hatched;

		monster()
			: hatched(false)
		{}

		void init()
		{
			hatched = true;
		}

		void update()
		{
			if(hatched)
			{
				auto char_at = level::current->find<character>().first;
				auto this_at = level::iterator;

				level::current->walk(sgn(char_at - this_at));
			}
		}

		void draw()
		{
			addch('m');
		}
	};
}