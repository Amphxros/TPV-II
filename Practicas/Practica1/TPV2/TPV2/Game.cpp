#include "Game.h"
#include "Entity.h"
#include "Manager.h"
#include"Component.h"

#include <SDL.h>

Game::Game(){

}
void Game::init() {

	mngr_ = new Manager();
	Entity* e = mngr_.addEntity();
	e->addComponent<Transform>(Vector2D(), Vector2D(), 150, 150, 0);


	
}