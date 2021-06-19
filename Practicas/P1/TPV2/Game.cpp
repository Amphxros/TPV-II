#include "Game.h"

#include "sdlutils/SDLUtils.h"
#include "utils/Vector2D.h"

#include "sdlutils/InputHandler.h"

#include "ecs/Manager.h"
#include "Transform.h"
#include "Image.h"
#include "FighterCtrl.h"
#include "Health.h"
#include "Gun.h"
#include "ShowAtOppositeSide.h"

#include "AsteroidsManager.h"
#include "GameCtrl.h"
#include "CollisionManager.h"
#include "State.h"

Game::Game()
{
	mngr_.reset(new Manager());
}

Game::~Game()
{
	
	mngr_.reset();
}

void Game::init()
{
	// Initialise the SDLGame singleton
	SDLUtils::init("Asteroids", 800, 600,
		"resources/config/resources.json");

	// reference to the SDLUtils Singleton. You could use it as a pointer as well,
	// I just prefer to use . instead of ->, it is just a matter of taste, nothing
	// else!
	//
	// you can also use the inline method sdlutils() that simply returns the value
	// of *SDLUtils::instance() --- it is defined at the end of SDLUtils.h
	//
	auto& sdl = *SDLUtils::instance();

	Entity* gManager = mngr_->addEntity();
	gManager->addComponent<State>();
	gManager->addComponent<AsteroidsManager>();
	gManager->addComponent<GameCtrl>();
	gManager->addComponent<CollisionManager>();



	Entity* player = mngr_->addEntity(); 
	player->addComponent<Transform>(Vector2D(sdl.width() / 2-25, sdl.height() / 2 -25), Vector2D(), 50, 50, 0);

	player->addComponent<Image>(&sdl.images().at("fighter"));
	player->addComponent<FighterCtrl>();
	player->addComponent<Health>(3, &sdl.images().at("heart"));
	player->addComponent<Gun>();
	player->addComponent<ShowAtOppositeSide>();
	mngr_->setHandler<Fighter>(player);



	//Manager* m = new Manager();
	//// store the 'renderer' in a local variable, just for convenience
	SDL_Renderer* renderer = sdl.renderer();


	// we can take textures from the predefined ones, and we can create a custom one as well

	
	// start the music in a loop
	//sdl.musics().at("beat").play();

	// reference to the input handler (we could use a pointer, I just . rather than ->).
	// you can also use the inline method ih() that is defined in InputHandler.h
	auto& ih = *InputHandler::instance();

	// a boolean to exit the loop
	bool exit_ = false;
	SDL_Event event;

	while (!exit_) {
		Uint32 startTime = sdl.currRealTime();

		// update the event handler
		ih.clearState();
		while (SDL_PollEvent(&event))
			ih.update(event);

		// exit when escape key is down
		if (ih.isKeyDown(SDLK_ESCAPE)) {
			exit_ = true;
		}
		mngr_->refresh();
		mngr_->update();

		// clear screen
		sdl.clearRenderer();

		mngr_->render();
		mngr_->getHandler<Fighter>()->render();


		// present new frame
		sdl.presentRenderer();

		Uint32 frameTime = sdl.currRealTime() - startTime;

		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
	}

	// stop the music
	Music::haltMusic();



	/*SDLUtils::init("Asteroids", 800, 600,
		"resources/config/resources.json");
	sdl = SDLUtils::instance();

	
	*/

}

void Game::start()
{
	/*
	bool exit = false;
	SDL_Event event;
	while(!exit){

		Uint32 startTime = sdlutils().currRealTime();
		ih().clearState();
		while (SDL_PollEvent(&event)) ih().update(event);
		if (ih().isKeyDown(SDLK_ESCAPE)) {
			exit = true;
		}

		mngr_->refresh();
		mngr_->update();

		sdl->clearRenderer();
		mngr_->render();
		sdl->presentRenderer();
		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
			}
	*/
	
}

void Game::update()
{

}

void Game::render()
{


}
