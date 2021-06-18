#include "ShowAtOppositeSide.h"

ShowAtOppositeSide::ShowAtOppositeSide()
{
}

ShowAtOppositeSide::~ShowAtOppositeSide()
{
}

void ShowAtOppositeSide::init()
{
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void ShowAtOppositeSide::update()
{
	if(tr_->getPos().getX()<0){
		tr_->setPos(sdlutils().width() - tr_->getW(), tr_->getPos().getY());
	}
	else if(tr_->getPos().getX() > sdlutils().width()){
		
		tr_->setPos(tr_->getW(), tr_->getPos().getY());
	}
	
	if(tr_->getPos().getY()<0){
		
		tr_->setPos(tr_->getPos().getX(),sdlutils().height() - tr_->getH() );
	}
	else if(tr_->getPos().getY() > sdlutils().height()){

		tr_->setPos(tr_->getPos().getX(), tr_->getH());
	}
	
}
