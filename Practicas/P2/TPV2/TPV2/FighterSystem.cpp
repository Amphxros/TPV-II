#include "FighterSystem.h"
#include "ecs/Manager.h"
#include "sdlutils/SDLUtils.h"
FighterSystem::FighterSystem()
{
}

FighterSystem::~FighterSystem()
{
}

void FighterSystem::onCollisionWithAsteroid(Entity* a)
{
}

void FighterSystem::init()
{
	Entity* fighter = manager_->addEntity();
	//fighter->addComponent<Transform>(Vector2D(sdlutils().width() / 2, sdlutils().height() / 2), Vector2D(), 150, 150, 0);
	//fighter->addComponent<Image>();
	//fighter->addComponent<ShowAtOppositeSide>();
}

void FighterSystem::update()
{
}
