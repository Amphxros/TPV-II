#include "Follow.h"

Follow::Follow()
{
}

Follow::~Follow()
{
}

void Follow::init()
{
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);

}

void Follow::update()
{
}
