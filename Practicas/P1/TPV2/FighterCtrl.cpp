#include "FighterCtrl.h"

FighterCtrl::FighterCtrl()
{
}

FighterCtrl::~FighterCtrl()
{
}

void FighterCtrl::init()
{
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void FighterCtrl::update()
{
}
