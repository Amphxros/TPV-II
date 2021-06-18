#include <iostream>
#include <SDL.h>

#include "sdlutils/sdlutils_demo.h"
#include "Game.h"

int main(int ac, char** av) {

	Game g;
	g.init();
	g.start();

	return 0;
}