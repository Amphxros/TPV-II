#include "DisableOnExit.h"

DisableOnExit::DisableOnExit():
	Component(), tr_(nullptr)
{
}

DisableOnExit::~DisableOnExit()
{
}

void DisableOnExit::init()
{
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void DisableOnExit::update()
{
	if(tr_->getPos().getX()<0 || tr_->getPos().getX()> sdlutils().width() || 
		tr_->getPos().getY()< 0 || tr_->getPos().getY()> sdlutils().height()){
		entity_->setActive(false);
	}

}
