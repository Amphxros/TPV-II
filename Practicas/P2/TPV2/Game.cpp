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


	/*Entity* gManager = mngr_->addEntity();
	gManager->addComponent<State>();
	gManager->addComponent<AsteroidsManager>(5000,10);
	gManager->addComponent<GameCtrl>();
	gManager->addComponent<CollisionManager>();
	mngr_->setHandler<GM>(gManager);

	Entity* player = mngr_->addEntity(); 
	player->addComponent<Transform>(Vector2D(sdlutils().width() / 2-25, sdlutils().height() / 2 -25), Vector2D(), 50, 50, 0);

	player->addComponent<Image>(&sdlutils().images().at("fighter"));
	player->addComponent<FighterCtrl>(10.0f,0.25f,3);
	player->addComponent<Health>(3, &sdlutils().images().at("heart"));
	player->addComponent<Gun>(50);
	player->addComponent<ShowAtOppositeSide>();
	mngr_->setHandler<Fighter>(player);*/


}

void Game::start(){
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
	
		// clear screen
		sdlutils().clearRenderer();
		//rendersystem here



		// present new frame
		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
	}

	// stop the music
	Music::haltMusic();
	
}

void Game::update()
{

}

void Game::render()
{


}
