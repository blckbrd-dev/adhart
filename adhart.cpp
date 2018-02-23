
#include <curses.h>
#include <iostream>

const int NEW_GAME = -1001;

#include "level.h"
#include "choice.h"
#include "character.h"
#include "monster.h"

WINDOW* window;
adhart::level* level;
adhart::character* player;
int depth;
int corridor_width;

typedef std::function<adhart::entity*()> constructor;

constructor* monsters = new constructor[2] {
	[]() { return new adhart::kobold; },
	[]() { return new adhart::ogre; }
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

bool is_vowel(char c) {
    c = tolower(c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

void check_new_game()
{
	if(player->floor == NEW_GAME)
	{
		depth = 1;
		corridor_width = 20;
		player = new adhart::character;
		level = nullptr;
		player->floor = 0;
	}	
}

void new_level_needed()
{
	if(level == nullptr) {
		level = new adhart::level(player, corridor_width, monsters, 2, depth * 5);
		adhart::level::current = level;

		if(depth == 1)
		{
			log("Welcome to adhart. We can only move forward.");
		}

		show();
	}	
}

void check_using_stairs()
{
	if(player->floor < 0)
	{
		// TODO: this message doesn't show up, fix it
		clog();
		log("Our gods do not permit going back.");
	}
	else if(player->floor > 0)
	{
		log("We descend even deeper! -- PRESS TO CONTINUE.");

		level = nullptr;
		depth++;
		corridor_width += depth;

		show();
		getch();
	}
}

void check_death()
{
	if(!player->alive)
	{
		log("You are dead. -- PRESS ANY KEY TO QUIT");
		getch();
		endwin();

		auto killer = player->killer->name;
		std::cout << "\nYou were killed by "
				  << (is_vowel(killer[0]) ? "an " : "a ") 
				  << killer 
				  << ", while roaming the " << depth;

		if(depth % 10 == 1)
			std::cout << "st";
		else if(depth % 10 == 2)
			std::cout << "nd";
		else if(depth % 10 == 3)
			std::cout << "rd";
		else 
			std::cout << "th";

		std::cout << " level of the dungeon.\n" << std::endl;
		exit(0);
	}
}

void draw_gui()
{
	char buffer[5];

	move(15, 1);

	printw("Power: %2d    ", player->power);
	printw("Toughness: %2d    ", player->toughness);
	printw("Level: %2d    ", player->lvl);
	printw("Depth: %2d    ", depth);

	move(17, 1);
	addstr("Live long and descend as far as you can, ");
	attron(A_BOLD); addstr("going boldly forward"); attroff(A_BOLD);
	addstr(".");

	move(18, 1);
	addstr("Sometimes, though, you might have to paddle back or wait.");

	move(19, 1);
	addstr("Use the ");
	attron(A_BOLD); addstr("features"); attroff(A_BOLD);
	addstr(" of the dungeon and its denizens ");
	attron(A_BOLD); addstr("against"); attroff(A_BOLD);
	addstr(" it!");

	move(21, 1);
	addstr("Use ");
	attron(A_BOLD); addstr("[LEFT]"); attroff(A_BOLD);
	addstr(" and ");
	attron(A_BOLD); addstr("[RIGHT]"); attroff(A_BOLD);
	addstr(" to move and attack.");

	move(22, 1);
	addstr("Wait a turn by pressing ");
	attron(A_BOLD); addstr("[SPACE]"); attroff(A_BOLD);
	addstr(".");

	move(23, 1);
	addstr("Exit anytime by pressing ");
	attron(A_BOLD); addstr("[Q]"); attroff(A_BOLD);
	addstr(".");
}

int main()
{
	srand(time(nullptr));

	init();

	depth = 1;
	corridor_width = 20;
	player = new adhart::character;

	while(true)
	{
		clog();

		check_new_game();
		new_level_needed();

		evaluate(input());

		check_using_stairs();

		draw_gui();
		show();	

		check_death();
	}

	return 0;
}
