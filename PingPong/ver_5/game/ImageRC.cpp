// This file is part of the course TPV2@UCM - Samir Genaim

#include "ImageRC.h"

#include "../sdlutils/macros.h"
#include "Container.h"

ImageRC::ImageRC(Texture *img) :
		img_(img) {

}

ImageRC::~ImageRC() {
}

void ImageRC::render(Container *c) {
	SDL_Rect dest = build_sdlrect(c->getPos(), c->getWidth(), c->getHeight());
	img_->render(dest);
}
