// This file is part of the course TPV2@UCM - Samir Genaim

#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "Container.h"
#include "EmptyRectRC.h"

EmptyRectRC::EmptyRectRC() :
		EmptyRectRC(build_sdlcolor(0xffffffff)) {
}

EmptyRectRC::EmptyRectRC(SDL_Color color) :
		color_(color) //
{
}

EmptyRectRC::~EmptyRectRC() {
}

void EmptyRectRC::render(Container *c) {
	auto pos_ = c->getPos();

	SDL_SetRenderDrawColor(sdlutils().renderer(), COLOREXP(color_));

	SDL_Rect rect = build_sdlrect(pos_.getX(), pos_.getY(), c->getWidth(),
			c->getHeight());

	SDL_RenderDrawRect(sdlutils().renderer(), &rect);

}
