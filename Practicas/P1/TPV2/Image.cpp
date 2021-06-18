#include "Image.h"

Image::Image(Texture* tex):
	Component(), tex_(tex), tr_(nullptr)
{
}

Image::~Image()
{
	delete tex_;
}

void Image::init()
{
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void Image::render()
{
	SDL_Rect dest;
	dest.x = tr_->getPos().getX();
	dest.x = tr_->getPos().getY();
	dest.w = tr_->getW();
	dest.h = tr_->getH();
	
	tex_->render(dest, tr_->getRotation());
}
