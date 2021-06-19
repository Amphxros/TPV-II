#include "State.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
State::State():
	Component(), gameWin(false), initMsg(nullptr), pauseMsg(nullptr), gameOverMsg(nullptr), gameWinMsg(nullptr), gameState(GameState::NEW)
{
}

State::~State()
{
}

void State::init()
{
	gameState = GameState::NEW;
	initMsg = &sdlutils().msgs().at("init");
	pauseMsg = &sdlutils().msgs().at("pause");
	gameOverMsg = &sdlutils().msgs().at("gameOver");
	gameWinMsg = &sdlutils().msgs().at("gameWin");

}


void State::render()
{
	SDL_Rect dest;

	switch (gameState){
	case GameState::NEW:
		dest.x = (int)(sdlutils().width()/2 - initMsg->width()) / 2;
		dest.y = (int)(sdlutils().height()- initMsg->height()) / 2 - 100;
		dest.w = (int)sdlutils().width() / 2;
		dest.h = (int)sdlutils().height() / 3;

		initMsg->render(dest, 0.0f);

		break;

	case GameState::PAUSE:
		dest.x = (int)((sdlutils().width()/2 - pauseMsg->width()) / 2);
		dest.y = (int)((sdlutils().height() - pauseMsg->height()) / 2 - 100);
		dest.w = (int)sdlutils().width()/2;
		dest.h = (int)sdlutils().height() / 3;

		pauseMsg->render(dest, 0.0f);
		break;

	case GameState::GAMEOVER:
		if(gameWin){
			dest.x = (int)(sdlutils().width()/2 - gameWinMsg->width()) / 2;
			dest.y = (int)(sdlutils().height() - gameWinMsg->height()) / 2 - 100;
			dest.w = (int)sdlutils().width() / 2;
			dest.h = (int)sdlutils().height() / 3;
			
			gameWinMsg->render(dest, 0.0f);
		}
	
		else {
			dest.x = (int)(sdlutils().width()/2 - gameOverMsg->width()) / 2;
			dest.y = (int)(sdlutils().height() - gameOverMsg->height()) / 2 - 100;
			dest.w = (int)sdlutils().width() / 2;
			dest.h = (int)sdlutils().height() / 3;

			gameOverMsg->render(dest, 0.0f);
		}
		break;
	}

	
}

