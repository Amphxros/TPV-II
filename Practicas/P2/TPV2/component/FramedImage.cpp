#include "FramedImage.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

FramedImage::FramedImage(Texture* tex, int rows, int cols, int r, int c, float frate):
	tex_(tex), timer(frate), lastTime(0)
{

	src.x = tex_->width() / cols * c;
	src.y = tex_->height() / rows * r;
	src.w = tex_->width() / cols;
	src.h = tex_->height() / rows;

	lastTime = sdlutils().currRealTime() - timer;
	posX = c;
	posY = r;
	iniFrame = Vector2D();
	dim = Vector2D(rows, cols);
}

FramedImage::~FramedImage()
{
}

void FramedImage::update()
{

	if (sdlutils().currRealTime() - lastTime > timer) {
		lastTime = sdlutils().currRealTime();
		if (posX != dim.getX() - 1) {
			posX++;
		}
		else {
			if (posY != dim.getY() - 1) {
				posY++;
				
			}
			else {
				posY = (int)iniFrame.getX();
			}
			posX = (int)iniFrame.getX();
		}
	}
	
}
//
//void FramedImage::render()
//{
//	SDL_Rect dest;
//	dest.x = (int)tr_->getPos().getX();
//	dest.y = (int)tr_->getPos().getY();
//	dest.w = (int)tr_->getW();
//	dest.h = (int)tr_->getH();
//	
//	tex_->render(src, dest, tr_->getRotation());
//}
