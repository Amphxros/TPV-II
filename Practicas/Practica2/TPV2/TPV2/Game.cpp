#include "Game.h"
#include "Entity.h"
#include "Manager.h"
#include"Component.h"

#include <SDL.h>

Game::Game(): mngr_(nullptr), renderer(nullptr), sdl(nullptr){
}

Game::~Game() {

	delete sdl;
	sdl = nullptr;

	delete mngr_;
	mngr_ = nullptr;
}

void Game::init() {

	SDLUtils::init("SDLGame Demo!", 800, 600,
		"resources/config/resources.json");
	sdl = SDLUtils::instance();
	
	mngr_=new Manager();
	renderer== sdl->renderer();

	gameSys = new GameCtrlSystem();
	gameSys->setManager(mngr_);
	gameSys->init();

	bulletSys = new BulletsSystem();
	bulletSys->setManager(mngr_);
	bulletSys->init();

	fighterSys = new FighterSystem();
	fighterSys->setManager(mngr_);
	fighterSys->init();
	
	fighterGunSys = new FighterGunSystem();
	fighterGunSys->setManager(mngr_);
	fighterGunSys->init();
	
	asteroidSys = new AsteroidsSystem(10,10,10);
	asteroidSys->setManager(mngr_);
	asteroidSys->init();

	collisionSys = new CollisionSystem();
	collisionSys->setManager(mngr_);
	collisionSys->init();
	
	renderSys = new RenderSystem();
	renderSys->setManager(mngr_);
	renderSys->init();
}

void Game::render(){
	sdl->clearRenderer();
	renderSys->update();
	gameSys->update();
	sdl->presentRenderer();
}

void Game::update()
{
	//definiremos el orden de actualizado de las distitas entidades con los sistemas
	fighterSys->update();
	fighterGunSys->update();
	asteroidSys->update();
	bulletSys->update();
	collisionSys->update();
	mngr_->refresh();
}

void Game::run()
{
	bool exit = false;
	SDL_Event event;

	while (!exit) {

		Uint32 startTime = sdlutils().currRealTime();
		ih().clearState();
		while (SDL_PollEvent(&event)){
			ih().update(event);
		}
		if (ih().isKeyDown(SDLK_ESCAPE)) {
			exit = true;
		}
		render();
		update();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
	}
}