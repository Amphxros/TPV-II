#pragma once

#include "sdlutils/InputHandler.h"
#include "sdlutils/macros.h"
#include "sdlutils/SDLUtils.h"
class Manager;
class Game
{
public:
	Game();

	void init();
	void run();
	void update();
	void render();

private:
	void createPlayer();
	void createGameManager();

	Manager* mngr_;
	SDLUtils* sdl;
	
	SDL_Renderer* renderer;
};

