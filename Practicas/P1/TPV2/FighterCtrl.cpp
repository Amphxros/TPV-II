#include "FighterCtrl.h"

#include "sdlutils/InputHandler.h"

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
