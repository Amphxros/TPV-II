#include "Game.h"
#include "Entity.h"
#include "Manager.h"
#include"Component.h"

#include <SDL.h>

Game::Game(){
	SDLUtils::init("SDLGame Demo!", 800, 600,
		"resources/config/resources.json");
	sdl = SDLUtils::instance();
	
	mngr_ = new Manager();
	renderer== sdl->renderer();

}
void Game::init() {

	auto &sdlLogo = sdl->images().at("sdl_logo");
	int width = sdl->width();
	int height = sdl->height();

	Entity* e = mngr_->addEntity();
	e->addComponent<Transform>(Vector2D(), Vector2D(), 150, 150, 0);
	e->addComponent<Image>(&sdlLogo);
	e->addComponent<ShowAtOppositeSide>(width,height);
	e->addComponent<FighterCtrl>();
	e->addComponent<DeAcceleration>(0.995);
	e->addComponent<Health>(3, &sdlLogo);
	
}

void Game::render(){
	sdl->clearRenderer();
	mngr_->render();
	sdl->presentRenderer();
}

void Game::update(){
	mngr_->update();
}

void Game::run(){
	while (true) {
		render();
		update();
	}
}