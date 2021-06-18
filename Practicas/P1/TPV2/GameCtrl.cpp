#include "GameCtrl.h"
#include "sdlutils/SDLUtils.h"
#include "ecs/Entity.h"
#include "sdlutils/InputHandler.h"

GameCtrl::GameCtrl()
{
}

GameCtrl::~GameCtrl()
{
}

void GameCtrl::init()
{
	gameState_ = entity_->getComponent<State>();
	astManager = entity_->getComponent<AsteroidsManager>();
}

void GameCtrl::update()
{

	if(ih().keyDownEvent()){
		if(ih().isKeyDown(SDL_SCANCODE_SPACE) && gameState_->getGameState()!=GameState::RUNNING){
			switch(gameState_->getGameState()){

				case GameState::NEW:

					break;

				case GameState::PAUSE:
					break;

				case GameState::GAMEOVER:

					break;
			}
		}
	}

}

void GameCtrl::onFighterCollision()
{
}

