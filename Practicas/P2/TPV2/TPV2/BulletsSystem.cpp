#include "BulletsSystem.h"

BulletsSystem::BulletsSystem()
{
}

BulletsSystem::~BulletsSystem()
{
}

void BulletsSystem::shoot(Vector2D pos, Vector2D vel, double width, double height)
{

}

void BulletsSystem::onCollisionWithAsteroid(Entity* b, Entity* a)
{
}

void BulletsSystem::init()
{
}

void BulletsSystem::update()
{
}

void BulletsSystem::receive(const Message& m)
{
	switch(m.type_){
	case _SHOOT:
		shoot(m.bullet_.pos, m.bullet_.vel,m.bullet_.w,m.bullet_.h)
		break;
	case _GAME_OVER_:
	case _ROUND_OVER_:
		active_ = false;
		break;
	}
}
