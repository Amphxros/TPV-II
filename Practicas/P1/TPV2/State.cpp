#include "State.h"
#include "sdlutils/SDLUtils.h"

State::State():
Component(), gameWin(false), initMsg(nullptr), pauseMsg(nullptr), gameOverMsg(nullptr), gameWinMsg(nullptr)
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
		dest.x = (sdlutils().width() - initMsg->width()) / 2;
		dest.y = (sdlutils().height() - initMsg->height()) / 2 - 100;
		dest.w = initMsg->width();
		dest.w = initMsg->height();

		initMsg->render(dest, 0.0f);

		break;

	case GameState::PAUSE:
		dest.x = (sdlutils().width() - pauseMsg->width()) / 2;
		dest.y = (sdlutils().height() - pauseMsg->height()) / 2 - 100;
		dest.w = pauseMsg->width();
		dest.w = pauseMsg->height();

		pauseMsg->render(dest, 0.0f);
		break;

	case GameState::GAMEOVER:
		if(gameWin){
			dest.x = (sdlutils().width() - gameWinMsg->width()) / 2;
			dest.y = (sdlutils().height() - gameWinMsg->height()) / 2 - 100;
			dest.w = gameWinMsg->width();
			dest.w = gameWinMsg->height();
			
			gameWinMsg->render(dest, 0.0f);
		}
	
		else {
			dest.x = (sdlutils().width() - gameOverMsg->width()) / 2;
			dest.y = (sdlutils().height() - gameOverMsg->height()) / 2 - 100;
			dest.w = gameOverMsg->width();
			dest.w = gameOverMsg->height();

			gameOverMsg->render(dest, 0.0f);
		}
		break;
	}

	
}