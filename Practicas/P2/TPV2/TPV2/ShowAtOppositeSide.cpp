#include "ShowAtOppositeSide.h"
#include "Transform.h"
#include "ecs/Entity.h"
#include "sdlutils/SDLUtils.h"
void ShowAtOppositeSide::update()
{
	Transform* tr_ = entity_->getComponent<Transform>();

	if (tr_->pos_.getX() < 0) {
		tr_->pos_.setX(sdlutils().width() - tr_->width_);
	}
	else if (tr_->pos_.getX() > sdlutils().width()) {

		tr_->pos_.setX(tr_->width_);
	}
	if (tr_->pos_.getY() < 0) {

		tr_->pos_.setY(sdlutils().height() - tr_->height_);
	}
	else if (tr_->pos_.getY() > sdlutils().height()) {

		tr_->pos_.setY(tr_->height_);
	}

}
