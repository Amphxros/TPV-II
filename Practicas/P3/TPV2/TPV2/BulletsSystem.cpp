#include "BulletsSystem.h"

#include "components/Transform.h"
#include "ecs/Manager.h"
#include "sdlutils/SDLUtils.h"
#include "NetworkSystem.h"
#include "ecs_defs.h"

BulletsSystem::BulletsSystem()
{
}

void BulletsSystem::init()
{
}

void BulletsSystem::update()
{
	auto entities = manager_->getEnteties();

	for (auto e : entities) {
		if (manager_->hasGroup<Bullet>(e)) {
			auto tr_ = manager_->getComponent<Transform>(e);
			tr_->pos_ = tr_->pos_ + tr_->vel_;
			if (tr_->pos_.getY() < 0) {
				manager_->setActive(e, false);
			}
			else if (tr_->pos_.getY() + tr_->height_ > sdlutils().height()) {

				manager_->setActive(e, false);
			}
			if (tr_->pos_.getX() < 0) {
				manager_->setActive(e, false);
			}
			else if (tr_->pos_.getX() + tr_->width_ > sdlutils().width()) {
				manager_->setActive(e, false);
			}
		}
	}

}

void BulletsSystem::shoot(Vector2D pos, Vector2D vel, double width, double height)
{
	Entity* e = manager_->addEntity();
	manager_->addComponent<Transform>(e, pos, vel, width, height, 0.0);
	manager_->addComponent<Image>(e, sdlutils().images().at("bullet"));
	manager_->setGroup<Bullet>(e, true);
}
