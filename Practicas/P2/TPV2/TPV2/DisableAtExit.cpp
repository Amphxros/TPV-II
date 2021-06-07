#include "DisableAtExit.h"
#include "Transform.h"
#include "ecs/Entity.h"
#include "sdlutils/SDLUtils.h"

void DisableAtExit::update() {
	Transform* t = entity_->getComponent<Transform>();
	assert(t != nullptr);

	if (t->pos_.getX() < 0 || t->pos_.getX() > sdlutils().width() || t->pos_.getY() < 0 || t->pos_.getY() > sdlutils().height()) {
		entity_->setActive(false);
	}
}