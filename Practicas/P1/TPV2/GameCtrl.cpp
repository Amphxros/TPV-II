#include "GameCtrl.h"
#include "sdlutils/SDLUtils.h"
#include "ecs/Entity.h"
#include "sdlutils/InputHandler.h"

GameCtrl::GameCtrl(): Component(), astManager(nullptr), gameState_(nullptr)
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
				case GameState::PAUSE:
					gameState_->changeState(GameState::RUNNING);
					astManager->initGame();
					std::cout << "init game" << std::endl;
					break;

				case GameState::GAMEOVER:
					gameState_->changeState(GameState::NEW);

					break;
			}
		}
	}

}

void GameCtrl::onFighterCollision()
{
}

