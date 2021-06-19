#include "GameCtrl.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Manager.h"

GameCtrl::GameCtrl(): 
	Component(), astManager(nullptr), gameState_(nullptr)
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
					gameState_->changeState(GameState::RUNNING);
					astManager->initGame();
					sdlutils().musics().at("imperial_march").play();
					break;
				case GameState::PAUSE:
					gameState_->changeState(GameState::RUNNING);
					astManager->initGame();
					sdlutils().musics().at("imperial_march").resumeMusic();
		
					break;

				case GameState::GAMEOVER:
					gameState_->changeState(GameState::NEW);

					break;
			}
		}
	}

}



