all: adhart.cpp character.h choice.h entity.h level.h monster.h spawner.h utility.h corpse.h
	g++ -g -std=c++11 -o adhart adhart.cpp -lncurses
