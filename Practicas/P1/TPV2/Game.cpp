#include "Game.h"

#include "sdlutils/SDLUtils.h"
#include "utils/Vector2D.h"


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

}

void Game::init()
{
	SDLUtils::init("Asteroids", 800, 600,
		"resources/config/resources.json");
	sdl = SDLUtils::instance();

	Entity* gManager = mngr_->addEntity();
	gManager->addComponent<State>();
	gManager->addComponent<AsteroidsManager>();
	gManager->addComponent<GameCtrl>();
	gManager->addComponent<CollisionManager>();
	gManager->setActive(true);


	Entity* player = mngr_->addEntity();
	player->addComponent<Transform>(Vector2D((sdlutils().width()/2) -75,(sdlutils().height()/2) -75 ), Vector2D(), 150, 150, 0);
	player->addComponent<Image>(&sdlutils().images().at("fighter"));
	player->addComponent<FighterCtrl>();
	player->addComponent<Health>();
	player->addComponent<Gun>();
	player->addComponent<ShowAtOppositeSide>();
	player->setActive(true);
	mngr_->setHandler<Fighter>(player);

}

void Game::start()
{
	bool exit = false;

	while(!exit){
		update();
		render();
	}
}

void Game::update()
{
	mngr_->refresh();
	mngr_->update();
}

void Game::render()
{
	sdl->clearRenderer();
	mngr_->render();
	sdl->presentRenderer();

}
