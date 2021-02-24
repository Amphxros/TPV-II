// This file is part of the course TPV2@UCM - Samir Genaim

#include "PaddleNoFill.h"

#include "../sdlutils/SDLUtils.h"

PaddleNoFill::PaddleNoFill(SDL_Color color) :
		Paddle(color) {

}

PaddleNoFill::~PaddleNoFill() {
}

void PaddleNoFill::render() {
	SDL_SetRenderDrawColor(sdlutils().renderer(), COLOREXP(color_));

	SDL_Rect rect = build_sdlrect(pos_.getX(), pos_.getY(), width_, height_);

	SDL_RenderDrawRect(sdlutils().renderer(), &rect);
}
