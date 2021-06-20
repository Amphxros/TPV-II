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
	default:
		break;
	}
}

void BulletsSystem::onCollisionWithAsteroid(Entity* a, Entity* b)
{
}

void BulletsSystem::shoot(Vector2D pos, Vector2D vel, double width, double height, double rotation)
{
	Entity* e = manager_->addEntity();
	manager_->addComponent<Transform>(e, pos, vel, width, height, rotation);
	manager_->addComponent<Image>(e, &sdlutils().images().at("fire"));

}