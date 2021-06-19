#include <iostream>
#include <SDL.h>

#include "Game.h"

int main(int ac, char** av) {

	//sdlutils_basic_demo();

	Game g;
	g.init();
	g.start();

	

	return 0;
}