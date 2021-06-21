#include "BulletsSystem.h"

#include "ecs/Manager.h"
#include "component/Transform.h"
#include "component/Image.h"
#include "sdlutils/SDLUtils.h"

BulletsSystem::BulletsSystem(): System()
{
}

BulletsSystem::~BulletsSystem()
{
}

void BulletsSystem::init()
{
}

void BulletsSystem::update()
{
	for (auto ent : manager_->getEnteties()) {
		if (manager_->hasGroup<Bullets>(ent)) {
			Transform* tr = manager_->getComponent<Transform>(ent);
			tr->setPos(tr->getPos() + tr->getDir());

			if (tr->getPos().getX() < 0 || tr->getPos().getX() > sdlutils().width()
				|| tr->getPos().getY() < 0 || tr->getPos().getY() > sdlutils().height()) {
				manager_->setActive(ent,false);
			}

		}
	}
}

void BulletsSystem::receive(const msg::Message& m)
{
	switch (m.id)
	{
	case msg::BULLET_SHOOT:
		shoot(m.bullet.p, m.bullet.v, m.bullet.w, m.bullet.h, m.bullet.r);
		break;
	case msg::COLLISIONBULLET:
		onCollisionWithAsteroid(m.col.a, m.col.b);
		break;
	default:
		break;
	}
}

void BulletsSystem::onCollisionWithAsteroid(Entity* a, Entity* b)
{
	manager_->setActive(b, false);
}

void BulletsSystem::shoot(Vector2D pos, Vector2D vel, double width, double height, double rotation)
{
	Entity* e = manager_->addEntity();
	manager_->setGroup<Bullets>(e,true);
	manager_->addComponent<Transform>(e, pos, vel, width, height, rotation);
	manager_->addComponent<Image>(e, &sdlutils().images().at("fire"));
	
	sdlutils().soundEffects().at("fire").play();

}