#include <iostream>
#include "Core_war.h"

int main(){ 
	coreWar::Core_war game;
	game.add_unit("unit2.red");
	game.add_unit("unit1.red");
	game.add_unit("unit3.red");
	int res = game.start(100000);
	std::cout << "победил игрок номер: " << res + 1 << std::endl;
	return 0;
}