// This file is part of the course TPV2@UCM - Samir Genaim

#include "PingPongRulePC.h"

#include "../sdlutils/SDLUtils.h"
#include "../utils/Collisions.h"
#include "GameManager.h"

PingPongRulePC::PingPongRulePC() {
}

PingPongRulePC::~PingPongRulePC() {
}

void PingPongRulePC::update(Container *c) {
	auto gm = static_cast<GameManager*>(c);
	auto ball = gm->getBall();
	auto leftPaddle = gm->getLeftPaddle();
	auto rightPaddle = gm->getRightPaddle();

	// check if ball hits paddles
	if (Collisions::collides(leftPaddle->getPos(), leftPaddle->getWidth(),
			leftPaddle->getHeight(), ball->getPos(), ball->getWidth(),
			ball->getHeight())
			|| Collisions::collides(rightPaddle->getPos(),
					rightPaddle->getWidth(), rightPaddle->getHeight(),
					ball->getPos(), ball->getWidth(), ball->getHeight())) {

		// change the direction of the ball, and increment the speed
		auto &vel = ball->getVel(); // the use of & is important, so the changes goes directly to the ball
		vel.setX(-vel.getX());
		vel = vel * 1.2;

		// play some sound
		sdlutils().soundEffects().at("paddle_hit").play();
	} else if (ball->getPos().getX() < 0)
		onBallExit(GameManager::LEFT, gm);
	else if (ball->getPos().getX() + ball->getWidth() > sdlutils().width())
		onBallExit(GameManager::RIGHT, gm);
}

void PingPongRulePC::onBallExit(GameManager::Side side, GameManager *gm) {
	auto &score = gm->getScore();
	auto &state = gm->getState();
	auto maxScore = gm->getMaxScore();

	assert(state == GameManager::RUNNING); // this should be called only when game is running

	if (side == GameManager::LEFT) {
		score[1]++;
	} else {
		score[0]++;
	}

	gm->getBall()->getPos().set(sdlutils().width() / 2 - 5,
			sdlutils().height() / 2 - 5);
	gm->getBall()->getVel().set(0, 0);

	if (score[1] < maxScore && score[1] < maxScore)
		state = GameManager::PAUSED;
	else
		state = GameManager::GAMEOVER;
}

