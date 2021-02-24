// This file is part of the course TPV2@UCM - Samir Genaim

#include "PaddleWithAI.h"
#include "../sdlutils/SDLUtils.h"

PaddleWithAI::PaddleWithAI(SDL_Color color, GameObject *ball) :
		Paddle(color), //
		ball_(ball) {
}

PaddleWithAI::~PaddleWithAI() {
}

void PaddleWithAI::handleInput() {
}

void PaddleWithAI::update() {

	if (ballComingTowardsPaddle()) {
		float diff = (ball_->getPos().getY() + ball_->getHeight() / 2.0f)
				- (pos_.getY() + height_ / 2.0f);
		if (abs(diff) < 10) {
			vel_.setY(0.0f);
		} else {
			vel_.setY(
					(diff > 0.0f ? 1.0f : -1.0f) * 1.0f
							* ball_->getVel().magnitude());
		}
	} else {
		float diff = (sdlutils().height() / 2.0f)
				- (pos_.getY() + height_ / 2.0f);
		if (abs(diff) < 10) {
			vel_.setY(0.0);
		} else {
			vel_.setY((diff > 0 ? 1 : -1) * 5.0f);
		}
	}

	Paddle::update();
}

bool PaddleWithAI::ballComingTowardsPaddle() {
	return (pos_.getX() < ball_->getPos().getX() && ball_->getVel().getX() < 0)
			|| (pos_.getX() > ball_->getPos().getX()
					&& ball_->getVel().getX() > 0);
}
