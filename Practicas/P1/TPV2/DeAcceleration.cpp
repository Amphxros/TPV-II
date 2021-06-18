#include "DeAcceleration.h"

DeAcceleration::DeAcceleration(double thrust):
	Component(), thrust_(thrust)
{
}

DeAcceleration::~DeAcceleration()
{
}

void DeAcceleration::init()
{
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void DeAcceleration::update()
{
	tr_->setDir(tr_->getDir() * thrust_);
}
