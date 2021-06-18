#include "FramedImage.h"

FramedImage::FramedImage(double thrust)
{
}

FramedImage::~FramedImage()
{
}

void FramedImage::init()
{
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void FramedImage::update()
{
}

void FramedImage::render()
{
}
