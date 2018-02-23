#pragma once
#include <string>

namespace adhart 
{
	struct entity
	{
		bool alive;
		std::string name;
		int power;
		int toughness;

		entity(std::string name, int p = 1, int t = 1)
			: alive(true)
			, name(name)
			, power(p)
			, toughness(t)
		{}

		virtual ~entity() {}
		virtual void init() {}

		virtual bool damage(entity* cause) {
			toughness -= cause->power;
			alive = toughness > 0;
			return !alive;
		}

		virtual void update() = 0;
		virtual void draw() = 0;
	};
}
