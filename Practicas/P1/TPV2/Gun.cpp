#include "Gun.h"

Gun::Gun(double time)
{
}

Gun::~Gun()
{
}

void Gun::init()
{
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void Gun::update()
{
}
