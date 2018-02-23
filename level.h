#pragma once

#include <vector>
#include <functional>
#include <set>
#include <utility>
#include "utility.h"
#include "entity.h"
#include "spawner.h"
#include "corpse.h"

namespace adhart
{
	struct level
	{
		static int iterator;
		static level* current;

		level(
			entity* player, 
			int length, 
			std::function<entity*()>* enemy_kinds, 
			int enemy_kinds_n,
			int density = 10)
			: player(player)
			, length(length)
			, entities(new entity*[length] { nullptr, })
			, next(new entity*[length] { nullptr, })
			, holesAbove(new spawner*[length] { nullptr, })
			, holesBelow(new spawner*[length] { nullptr, })
		{
			entities[0] = player;

			for(int i = 0; i < length; i++) {
				if(rand() % 100 <= density)
					holesAbove[i] = new spawner(random_from_array(enemy_kinds, enemy_kinds_n));

				if(rand() % 100 <= density)
					holesBelow[i] = new spawner(random_from_array(enemy_kinds, enemy_kinds_n));
			}
		}

		~level()
		{
			if(entities != nullptr)
				delete[] entities;

			if(next != nullptr)
				delete[] next;

			if(holesAbove != nullptr)
				delete[] holesAbove;

			if(holesBelow != nullptr)
				delete[] holesBelow;
		}

		int walk(int dir)
		{
			return walk(level::iterator, level::iterator + dir);
		}

		int walk(int from, int to)
		{
			if(to < 0) 
			{
				return -1;
			}

			if(to >= length) 
			{
				entities[from] = nullptr;
				next[from] = nullptr;
				return 1;
			}

			if(entities[from] != nullptr
			   && next[to] == nullptr)
			{
				next[from] = nullptr;
				next[to] = entities[from];
			}
			else if(entities[from] != nullptr
				&& next[to] != nullptr)
			{
				if(next[to]->alive)
				{
					if(next[to]->damage(next[from]))
						next[to] = new corpse(next[to]);
				}
				else
				{
					next[from] = nullptr;
					next[to] = entities[from];
				}
			}

			return 0;
		}

		void update()
		{
			int player_position = -1;
			for(int i = 0; i < length; i++) 
			{
				next[i] = entities[i];
				if(entities[i] == player)
					player_position = i;
			}

			level::iterator = player_position;
			player->update();

			for(int i = 0; i < length; i++)
			{
				level::iterator = i;
				if(entities[i] != nullptr && entities[i] != player &&
					entities[i]->alive)
					entities[i]->update();

				if(holesBelow[i] != nullptr) {
					if(holesBelow[i]->current == spawner::state::SPAWNED
					   && next[i] == nullptr) {
						holesBelow[i]->spawn->init();
						next[i] = holesBelow[i]->spawn;
						holesBelow[i]->clear();
					}

					holesBelow[i]->update();
				}

				if(holesAbove[i] != nullptr) {
					if(holesAbove[i]->current == spawner::state::SPAWNED
					   && next[i] == nullptr) {
						holesAbove[i]->spawn->init();
						next[i] = holesAbove[i]->spawn;
						holesAbove[i]->clear();
					}

					holesAbove[i]->update();
				}
			}

			for(int i = 0; i < length; i++)
				entities[i] = next[i];
		}

		void draw()
		{
			int x, y;
			getyx(stdscr, y, x);

			for(int i = 0; i < length; i++)
			{
				if(holesAbove[i] != nullptr)
					holesAbove[i]->draw();
				else
					addch('#');
			}

			move(y + 1, x - 1);
			addch('>');
			for(int i = 0; i < length; i++)
			{
				if(entities[i] != nullptr)
					entities[i]->draw();
				else
					addch('.');
			}
			addch('>');

			move(y + 2, x);
			for(int i = 0; i < length; i++)
			{
				if(holesBelow[i] != nullptr)
					holesBelow[i]->draw();
				else
					addch('#');
			}

			move(y, x);
		}

		template<typename T>
		std::pair<int, T*> find()
		{
			for(int i = 0; i < length; i++)
			{
				if(entities[i] != nullptr 
				   && dynamic_cast<T*>(entities[i]) != nullptr)
				{
					return std::pair<int, T*>(i, dynamic_cast<T*>(entities[i]));
				}
			}

			return std::pair<int, T*>(-1, nullptr);
		}

	private:
		int length;
		entity* player;
		entity** entities;
		entity** next;
		spawner** holesAbove;
		spawner** holesBelow;
	};
}

int adhart::level::iterator = 0;
adhart::level* adhart::level::current = nullptr;
