#include <iostream>
#include <SDL.h>

#include "sdlutils/sdlutils_demo.h"
#include "Game.h"

int main(int ac, char** av) {

	//sdlutils_basic_demo();

	Game* g= new Game();
	g->init();
	g->start();

	delete g;

	return 0;
}