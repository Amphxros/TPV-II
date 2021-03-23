#include "Game.h"
#include "Entity.h"
#include "Manager.h"
#include"Component.h"

#include <SDL.h>

Game::Game(){

}
void Game::init() {
		SDLUtils::init("SDLGame Demo!", 800, 600,
			"resources/config/resources.json");

	mngr_ = new Manager();
	sdl = SDLUtils::instance();
	renderer== sdl->renderer();
	auto &sdlLogo = sdl->images().at("sdl_logo");


	Entity* e = mngr_->addEntity();
	e->addComponent<Transform>(Vector2D(), Vector2D(), 150, 150, 0);
	e->addComponent<Image>(&sdlLogo);
	
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