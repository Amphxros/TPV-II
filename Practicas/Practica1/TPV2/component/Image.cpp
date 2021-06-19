#include "Image.h"
#include "../ecs/Entity.h"
Image::Image(Texture* tex):
	Component(), tex_(tex), tr_(nullptr)
{
}

Image::~Image()
{

}

void Image::init()
{
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void Image::render()
{
	SDL_Rect dest;
	dest.x = (int)tr_->getPos().getX();
	dest.y = (int)tr_->getPos().getY();
	dest.h = (int)tr_->getW();
	dest.w = (int)tr_->getH();
	
	tex_->render(dest, tr_->getRotation());
	assert(tr_ != nullptr && tex_!=nullptr);
}
