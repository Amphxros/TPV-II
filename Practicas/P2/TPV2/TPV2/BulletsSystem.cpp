#include "BulletsSystem.h"
#include "messages.h"
#include "ecs/Manager.h"
#include "DisableAtExit.h"
#include "AsteroidSystem.h"
BulletsSystem::BulletsSystem()
{
}

BulletsSystem::~BulletsSystem()
{
}

void BulletsSystem::shoot(Vector2D pos, Vector2D vel, double width, double height)
{
	Entity * e = manager_->addEntity();
	manager_->addComponent<Transform>(e, pos, vel,width, height);
	manager_->addComponent<DisableAtExit>(e);
	manager_->setGroup<Bullet>(e, true);
	
}

void BulletsSystem::onCollisionWithAsteroid(Entity* b, Entity* a)
{
	manager_->setActive(b, false);
	//b->setActive(false);
}

void BulletsSystem::init()
{
}

void BulletsSystem::update()
{
	if (!active_) {
		return;
	}
	//auto entities = manager_->getEnteties();
	//for (auto e : entities) {
	//	if (e->hasGroup<Bullet>()) {
	//		e->update();
	//	}
	//}
}

void BulletsSystem::receive(const Message& m)
{
	auto entities = manager_->getEnteties();
	switch(m.type_){
		case _SHOOT:
			shoot(m.bullet_.pos, m.bullet_.vel, m.bullet_.w, m.bullet_.h);
			break;
		case _GAME_OVER_:
		case _ROUND_OVER_:
		//	for (auto e : entities) {
		//		if (e->hasGroup<Bullet>()) {
		//			e->setActive(false);
		//		}
		//	}
			active_ = false;
			break;
		case _COLLISION_ASTEROID_BULLET:
			onCollisionWithAsteroid(m.entity_.entityB, m.entity_.entityA);
			break;
		default:
			active_ = true;
			break;
	}
}
