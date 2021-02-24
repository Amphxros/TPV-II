// This file is part of the course TPV2@UCM - Samir Genaim

#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "Container.h"
#include "FilledRectRC.h"

FilledRectRC::FilledRectRC() :
		FilledRectRC(build_sdlcolor(0xffffffff)) {
}

FilledRectRC::FilledRectRC(SDL_Color color) :
		color_(color) //
{
}

FilledRectRC::~FilledRectRC() {
}

void FilledRectRC::render(Container *c) {
	auto pos_ = c->getPos();

	SDL_SetRenderDrawColor(sdlutils().renderer(), COLOREXP(color_));

	SDL_Rect rect = build_sdlrect(pos_.getX(), pos_.getY(), c->getWidth(),
			c->getHeight());

	SDL_RenderFillRect(sdlutils().renderer(), &rect);

}
