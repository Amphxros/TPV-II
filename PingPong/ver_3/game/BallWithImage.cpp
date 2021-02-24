// This file is part of the course TPV2@UCM - Samir Genaim

#include "BallWithImage.h"

#include "../sdlutils/macros.h"
#include "../sdlutils/Texture.h"

BallWithImage::BallWithImage(Texture *img) :
		img_(img) {

}

BallWithImage::~BallWithImage() {
}

void BallWithImage::render() {
	SDL_Rect dest = build_sdlrect(pos_, width_, height_);
	img_->render(dest);
}
