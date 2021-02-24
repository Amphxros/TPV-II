// This file is part of the course TPV2@UCM - Samir Genaim

#include "Paddle.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"

Paddle::Paddle() :
		Paddle(build_sdlcolor(0xffffffff)) //
{
}

Paddle::Paddle(SDL_Color color) :
		color_(color), //
		up_(SDL_SCANCODE_UP), //
		down_(SDL_SCANCODE_DOWN), //
		stop_(SDL_SCANCODE_LEFT), //
		speed_(10.0f) //
{
}

Paddle::~Paddle() {

}

void Paddle::handleInput() {

	if (ih().keyDownEvent()) {
		if (ih().isKeyDown(up_)) {
			vel_.setY(-speed_);
		} else if (ih().isKeyDown(down_)) {
			vel_.setY(speed_);
		} else if (ih().isKeyDown(stop_)) {
			vel_.setY(0.0f);
		}
	}
}

void Paddle::update() {
	pos_ = pos_ + vel_;

	if (pos_.getY() < 0) {
		pos_.setY(0);
		vel_.setY(0);
	} else if (pos_.getY() + height_ > sdlutils().height()) {
		vel_.setY(0);
		pos_.setY(sdlutils().height() - height_);
	}

}

void Paddle::render() {
	SDL_SetRenderDrawColor(sdlutils().renderer(), COLOREXP(color_));

	SDL_Rect rect = build_sdlrect(pos_.getX(), pos_.getY(), width_, height_);

	SDL_RenderFillRect(sdlutils().renderer(), &rect);
}
