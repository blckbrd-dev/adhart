#pragma once

namespace adhart 
{
	struct entity
	{
		bool alive;

		entity() 
			: alive(true)
		{}

		virtual ~entity() {}
		virtual void init() {}
		virtual void death(entity* cause) {
			alive = false;
		}

		virtual void update() = 0;
		virtual void draw() = 0;
	};
}
