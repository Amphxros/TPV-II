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
	Vector2D vel = tr_->getDir() * thrust_;
	tr_->setDir(vel);
}
