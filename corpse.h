#pragma once

#include "entity.h"

namespace adhart
{
	struct corpse : public entity
	{
		corpse(entity* deceased)
		{
			alive = false;
		}

		void update() 
		{}

		void draw()
		{
			addch('%');
		}
	};
}