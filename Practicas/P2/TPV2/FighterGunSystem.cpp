#include "FighterGunSystem.h"
#include "ecs/Manager.h"
FighterGunSystem::FighterGunSystem():System(), active(false)
{
}

FighterGunSystem::~FighterGunSystem()
{
}

void FighterGunSystem::init()
{
	Entity* e = manager_->getHandler<Fighter>();
	tr_ = manager_->getComponent<Transform>(e);
	assert(tr_ != nullptr);
}

void FighterGunSystem::update()
{
	if (active) {


	}
}

void FighterGunSystem::receive(const msg::Message& m)
{
	switch (m.id)
	{
	case msg::START_GAME:
		active = true;
		break;
	case msg::ROUNDOVER:
	case msg::GAMEOVER:
		active = false;
		break;
	default:
		break;
	}
}
