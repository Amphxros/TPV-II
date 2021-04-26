#pragma once

#include "sdlutils/InputHandler.h"
#include "sdlutils/macros.h"
#include "sdlutils/SDLUtils.h"
#include "System.h"
class Manager;
class Game
{
public:
	Game();
	~Game();

	void init();
	void run();

private:
	void update();
	void render();

	void createPlayer();
	void createGameManager();

	Manager* mngr_;
	SDLUtils* sdl;
	
	AsteroidsSystem* asteroidSys;
	BulletsSystem* bulletSys;
	FighterSystem* fighterSys;
	FighterGunSystem* fighterGunSys;
	CollisionSystem* collisionSys;
	RenderSystem* renderSys;
	GameCtrlSystem* gameSys;

	SDL_Renderer* renderer;
};


