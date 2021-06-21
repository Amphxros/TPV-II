#include "Game.h"

#include "sdlutils/SDLUtils.h"
#include "utils/Vector2D.h"

#include "sdlutils/InputHandler.h"

#include "ecs/Manager.h"
#include "component/Transform.h"
#include "component/Image.h"
#include "component/FighterCtrl.h"
#include "component/Health.h"
#include "component/Gun.h"
#include "component/ShowAtOppositeSide.h"
		 
#include "component/AsteroidsManager.h"
#include "component/GameCtrl.h"
#include "component/CollisionManager.h"
#include "component/State.h"

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

	gameSys_ = mngr_->addSystem<GameCtrlSystem>();
	astSys = mngr_->addSystem<AsteroidSystem>();
	bulletSys_ = mngr_->addSystem<BulletsSystem>();
	collisionSys_ = mngr_->addSystem<CollisionSystem>();
	fighterSys_ = mngr_->addSystem<FighterSystem>();
	renderSys_ = mngr_->addSystem<RenderSystem>();


}

void Game::start() {
	// reference to the input handler (we could use a pointer, I just . rather than ->).
	// you can also use the inline method ih() that is defined in InputHandler.h


	// a boolean to exit the loop
	bool exit_ = false;
	SDL_Event event;

	while (!exit_) {
		Uint32 startTime = sdlutils().currRealTime();

		// update the event handler
		ih().clearState();
		while (SDL_PollEvent(&event))
			ih().update(event);

		// exit when escape key is down
		if (ih().isKeyDown(SDLK_ESCAPE)) {
			exit_ = true;
		}
		mngr_->refresh();

		gameSys_->update();
		astSys->update();
		bulletSys_->update();
		collisionSys_->update();
		fighterSys_->update();

		// clear screen
		sdlutils().clearRenderer();
		renderSys_->update();
		// present new frame
		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
	}

	// stop the music
	Music::haltMusic();

}