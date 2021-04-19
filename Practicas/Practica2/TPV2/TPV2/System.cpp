#include "System.h"
#include "Manager.h"
System::System()
{
}

System::System(ecs::SystemID id): id_(id)
{
}

GameCtrlSystem::GameCtrlSystem(): 
	System(ecs::GameCtrlSys), gs(GameState::NEW)
{
}

GameCtrlSystem::~GameCtrlSystem()
{
}

void GameCtrlSystem::onFighterDeath()
{

}

void GameCtrlSystem::onAsteroidsExtinction()
{
}

void GameCtrlSystem::init()
{
}

void GameCtrlSystem::update()
{
}

AsteroidsSystem::AsteroidsSystem(int numAsteroid)
{
}

AsteroidsSystem::~AsteroidsSystem()
{
}

void AsteroidsSystem::init()
{
}

void AsteroidsSystem::update()
{
}

BulletsSystem::BulletsSystem(): System(ecs::BulletSys)
{
}

BulletsSystem::~BulletsSystem()
{
}

void BulletsSystem::init()
{
	gameSys = mngr->getSystem<GameCtrlSystem>(ecs::GameCtrlSys);
}

void BulletsSystem::update()
{
	for (auto b : mngr->getEntities()) {
		if (b->hasGroup(ecs::BulletsGroup) && gameSys->getGameState()==GameState::RUNNING) {
			b->update();
		}
	}
}

void BulletsSystem::shoot(Vector2D pos, Vector2D vel, double width, double height)
{
	Entity* e = mngr->addEntity();
	e->addComponent<Transform>(pos, vel, width, height, vel.angle(Vector2D(0.0f, 1.0f)));
	e->addComponent<Image>(sdlutils().images().at("Bullet"));
	e->addComponent<DisableOnExit>(sdlutils().width(), sdlutils().height());
	e->setGroup(ecs::BulletsGroup, true);
	mngr->setHandler(e, ecs::BulletsHndlr);
}

void BulletsSystem::onCollisionWithAsteroid(Entity* b, Entity* a)
{
}

CollisionSystem::CollisionSystem()
{
}

void CollisionSystem::init()
{
}

void CollisionSystem::update()
{
}

FighterGunSystem::FighterGunSystem(): System(ecs::FighterGunSys)
{
}

FighterGunSystem::~FighterGunSystem()
{
}

void FighterGunSystem::init()
{
	bulletSys = mngr->getSystem<BulletsSystem>(ecs::BulletSys);
	assert(bulletSys != nullptr);
}

void FighterGunSystem::update()
{

}

RenderSystem::RenderSystem(): System(ecs::RenderSys)
{
}

void RenderSystem::init()
{
}

void RenderSystem::update()
{
	for (auto e : mngr->getEntities()) {
		e->render();
	}
}

FighterSystem::FighterSystem(): System(ecs::FighterSys)
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
	Entity* fighter = mngr->addEntity();
	fighter->addComponent<Transform>(Vector2D((sdlutils().width / 2) - 75, (sdlutils().height / 2) - 75), 150, 150, 0);
	fighter->addComponent<ShowAtOppositeSide>(sdlutils().width, sdlutils().height());
	fighter->addComponent<FighterCtrl>(0.5);
	fighter->addComponent<DeAcceleration>(0.995);
	fighter->addComponent<Health>(3);

	mngr->setHandler(fighter, ecs::FighterHndlr);
	fighter->setGroup(ecs::Fighter, true);

	gameSys_ = mngr->getSystem<GameCtrlSystem>(ecs::GameCtrlSys);
}

void FighterSystem::update()
{
}
