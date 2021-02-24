// This file is part of the course TPV2@UCM - Samir Genaim

#include "GameCtrlIC.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "GameManager.h"

GameCtrlIC::GameCtrlIC() {
}

GameCtrlIC::~GameCtrlIC() {
}

void GameCtrlIC::handleInput(Container *c) {
	auto gm = static_cast<GameManager*>(c);
	auto &state = gm->getState();
	auto &score = gm->getScore();

	if (state != GameManager::RUNNING) {
		if (ih().isKeyDown(SDL_SCANCODE_SPACE)) {
			switch (state) {
			case GameManager::NEWGAME:
				moveBall(gm);
				state = GameManager::RUNNING;
				break;
			case GameManager::PAUSED:
				moveBall(gm);
				state = GameManager::RUNNING;
				break;
			case GameManager::GAMEOVER:
				state = GameManager::NEWGAME;
				score[0] = score[1] = 0;
				break;
			default:
				break;
			}
		}
	}

}


void GameCtrlIC::moveBall(GameManager *gm) {
	auto &r = sdlutils().rand();

	int dx = 1 - 2 * r.nextInt(0, 2); // 1 or -1
	int dy = 1 - 2 * r.nextInt(0, 2); // 1 or -1

	Vector2D v(dx * r.nextInt(2, 7), dy * r.nextInt(2, 7));
	gm->getBall()->getVel().set(v.normalize() * 2);
}
