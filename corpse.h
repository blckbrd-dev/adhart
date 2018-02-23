#pragma once

#include "entity.h"

namespace adhart
{
	struct corpse : public entity
	{
		corpse(entity* deceased)
			: entity("corpse", 0, 0)
		{
			alive = false;
		}

		void update() 
		{}

		void draw()
		{
			addch('%');
		}

		bool damage(entity* e)
		{
			return true;
		}
	};
}