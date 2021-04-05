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

	createPlayer();
	createGameManager();
}

void Game::render(){
	sdl->clearRenderer();
	mngr_->render();
	sdl->presentRenderer();
}

void Game::createPlayer()
{
	auto& fighter = sdl->images().at("fighter");

	int width = sdl->width();
	int height = sdl->height();

	Entity* e = mngr_->addEntity();
	e->addComponent<Transform>(Vector2D(width/2, height/2), Vector2D(), 50, 50, 0);
	e->addComponent<Image>(&fighter);
	e->addComponent<ShowAtOppositeSide>(width, height);
	e->addComponent<FighterCtrl>(0.5);
	e->addComponent<DeAcceleration>(0.995);
	e->addComponent<Health>(3);
	e->addComponent<Gun>(5000);

	mngr_->setHandler(e,ecs::FighterHndlr);
	e->setGroup(ecs::Fighter, true);
}

void Game::createGameManager()
{
	Entity* gm = mngr_->addEntity();
	gm->addComponent<State>();
	gm->addComponent<AsteroidsManager>(10, 5000, 10, 10);
	gm->addComponent<GameCtrl>();
	gm->addComponent<CollisionsManager>();

	gm->setGroup(ecs::Other,true);
}

void Game::update()
{
	mngr_->refresh();
	mngr_->update();
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