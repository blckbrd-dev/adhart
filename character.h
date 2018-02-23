#pragma once

namespace adhart 
{
	struct character : public entity
	{
		choice decision;
		int floor;

		character() 
			: decision(NONE)
			, floor(0)
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
					// todo: do something here
					break;
				case JUMP:
					// todo: do something here
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
			addch('@');
		}		
	};
}