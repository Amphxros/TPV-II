#include "FighterGunSystem.h"
#include "Transform.h"
#include "messages.h"
#include "ecs/Manager.h"
FighterGunSystem::FighterGunSystem()
{
}

FighterGunSystem::~FighterGunSystem()
{
}

void FighterGunSystem::init()
{
}

void FighterGunSystem::update()
{
	if (!active_) {
		return;
	}

	//Transform* trFighter = manager_->getHandler<Fighter>()->getComponent<Transform>();

}

void FighterGunSystem::receive(const Message& m)
{
	switch (m.type_)
	{
	case _ROUND_START_:
		active_ = true;
		break;
	case _ROUND_OVER_:
		active_ = false;
		break;
	case _GAME_START_:
		active_ = true;
		break;
	case _GAME_OVER_:
		active_ = false;
		break;
	default:
		break;
	}

}
