// This file is part of the course TPV2@UCM - Samir Genaim

#include "RenderSystem.h"

#include "../components/Image.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"

RenderSystem::RenderSystem() :
		isRunning_(false), //
		isGameOver_(false), //
		isNewGame_(false), //
		pacmanWon_(false), //
		remainingRounds_(0), //
		roundImg_(nullptr), //
		winnerMsg_(nullptr), //
		loserMsg_(nullptr), //
		gameOverMsg_(nullptr), //
		continueMsg_(nullptr), //
		startMsg_(nullptr) {
}

RenderSystem::~RenderSystem() {
}

void RenderSystem::init() {
	roundImg_ = &sdlutils().images().at("heart");
	winnerMsg_ = &sdlutils().msgs().at("winner");
	loserMsg_ = &sdlutils().msgs().at("loser");
	gameOverMsg_ = &sdlutils().msgs().at("gameover");
	continueMsg_ = &sdlutils().msgs().at("continue");
	startMsg_ = &sdlutils().msgs().at("start");
}

void RenderSystem::update() {
	drawEntitiesWithImage();
	drawRounds();
	drawMsgs();
}

void RenderSystem::receive(const Message &msg) {
	switch (msg.type_) {
	case _ROUND_START_:
		isRunning_ = true;
		isNewGame_ = false;
		remainingRounds_ = msg.round_.remainingRounds_;
		break;
	case _ROUND_OVER_:
		isRunning_ = false;
		remainingRounds_ = msg.round_.remainingRounds_;
		break;
	case _GAME_START_:
		isGameOver_ = false;
		isNewGame_ = true;
		pacmanWon_ = msg.round_.pacmanWon_;
		remainingRounds_ = msg.round_.remainingRounds_;
		break;
	case _GAME_OVER_:
		isGameOver_ = true;
		pacmanWon_ = msg.round_.pacmanWon_;
		remainingRounds_ = msg.round_.remainingRounds_;
		break;
	default:
		break;
	}
}

void RenderSystem::drawMsgs() {

	// message when game is not running
	if (!isRunning_) {

		auto w = sdlutils().width();
		auto h = sdlutils().height();

		// mensaje de GameOver + Winner
		if (isGameOver_) {

			gameOverMsg_->render((w - gameOverMsg_->width()) / 2,
					(h - gameOverMsg_->height()) / 2 - 50);

			auto t = pacmanWon_ ? winnerMsg_ : loserMsg_;
			sdlutils().msgs().at(pacmanWon_ ? "winner" : "loser");
			t->render((w - t->width()) / 2, (h - t->height()) / 2 - 80);

		}

		// mensaje de start/continuar
		if (isNewGame_) {
			startMsg_->render((w - startMsg_->width()) / 2,
					h / 2 + startMsg_->height() * 2);
		} else {
			continueMsg_->render((w - continueMsg_->width()) / 2,
					h / 2 + continueMsg_->height() * 2);
		}
	}
}

void RenderSystem::drawEntitiesWithImage() {

	// dibujar todas la entidades que tienen Imagen, se puede
	// hacer por grupo también
	for (Entity *e : manager_->getEnteties()) {
		if (manager_->hasComponent<Image>(e)) {
			Image *img = manager_->getComponent<Image>(e);
			Transform *tr = manager_->getComponent<Transform>(e);

			auto &src = img->nextFrame();
			auto dest = build_sdlrect(tr->pos_, tr->width_, tr->height_);
			img->tex_->render(src, dest, tr->rotation_);
		}
	}

}

void RenderSystem::drawRounds() {
	SDL_Rect dest { 0, 5, 25, 25 };
	for (int i = 0; i < remainingRounds_; i++) {
		dest.x = i * 26;
		roundImg_->render(dest);
	}
}

