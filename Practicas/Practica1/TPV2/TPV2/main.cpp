#include <iostream>
#include <SDL.h>

#include "Game.h"
int main(int ac, char **av) {

	//sdlutils_basic_demo();
	Game g=Game();
	g.init();
	g.run();

	return 0;
}

