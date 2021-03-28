#include "Game.h"
#include "Entity.h"
#include "Manager.h"
#include"Component.h"

#include <SDL.h>

Game::Game(){
	SDLUtils::init("SDLGame Demo!", 800, 600,
		"resources/config/resources.json");
	sdl = SDLUtils::instance();
	
	mngr_=new Manager();
	renderer== sdl->renderer();

}
void Game::init() {


}

void Game::render(){
	sdl->clearRenderer();
	mngr_->render();
	sdl->presentRenderer();
}

void Game::createPlayer()
{

	auto& sdlLogo = sdl->images().at("sdl_logo");

	int width = sdl->width();
	int height = sdl->height();

	Entity* e = mngr_->addEntity();
	e->addComponent<Transform>(Vector2D(), Vector2D(), 150, 150, 0);
	e->addComponent<Image>(&sdlLogo);
	e->addComponent<ShowAtOppositeSide>(width, height);
	e->addComponent<FighterCtrl>();
	e->addComponent<DeAcceleration>(0.995);
	e->addComponent<Health>(3, &sdlLogo);

	e->setActive(true);

}

void Game::createGameManager()
{
	Entity* gm = mngr_->addEntity();

}

void Game::update(){
	mngr_->update();
	mngr_->refresh();
}

void Game::run(){
	bool exit = false;
	SDL_Event event;

	createPlayer();
	while (!exit) {
		Uint32 startTime = sdlutils().currRealTime();
		ih().clearState();
		while (SDL_PollEvent(&event))
			ih().update(event);

		render();
		update();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
	}
}