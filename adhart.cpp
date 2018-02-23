
#include <curses.h>
#include <iostream>

#include "level.h"
#include "choice.h"
#include "character.h"
#include "monster.h"

WINDOW* window;
adhart::level* level;
adhart::character* player;

typedef std::function<adhart::entity*()> constructor;

constructor* monsters = new constructor[1] {
	[]() { return new adhart::monster; }
};

void init()
{
	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	noecho();

	int h, w;
	getmaxyx(stdscr, h, w);
	window = newwin(h, w, 1, 1);
}

adhart::choice input()
{
	int ch = getch();
	switch(ch) {
		case KEY_LEFT:
			return adhart::choice::LEFT;
		case KEY_RIGHT:
			return adhart::choice::RIGHT;
		case ' ':
			return adhart::choice::WAIT;
		case 'P':
		case 'p':
			return adhart::choice::PRAY;
		case 'Q':
		case 'q':
			return adhart::choice::QUIT;
		case 10:	// enter
			return adhart::choice::YES;
		case KEY_BACKSPACE:
			return adhart::choice::NO;
		default:
			return adhart::choice::NONE;
	}
}

void show()
{
	move(5, 15);
	if(level != nullptr)
		level->draw();
	move(0, 0);
	refresh();
}

void evaluate(adhart::choice choice)
{
	player->decision = choice;
	if(level != nullptr)
		level->update();
}

int main()
{
	srand(time(nullptr));

	init();

	int depth = 1;
	int corridor_width = 20;
	player = new adhart::character;

	while(true)
	{
		// to make log messages disappear
		move(0, 0);
		addstr("										 	");

		if(level == nullptr) {
			level = new adhart::level(player, corridor_width, monsters, 1, depth * 5);
			adhart::level::current = level;

			show();
		}

		evaluate(input());
		if(player->floor < 0)
		{
			move(0, 0);
			addstr("Our gods do not permit going back.          ");
		}

		if(player->floor > 0)
		{
			move(0, 0);
			addstr("We descend even deeper! -- PRESS TO CONTINUE");
			show();
			level = nullptr;
			depth++;
			corridor_width += depth;

			show();
			getch();
		}

		show();
	}

	return 0;
}
