#include "System.h"
#include "Manager.h"
#include "sdlutils/InputHandler.h"

//System//

System::System()
{
}

System::System(ecs::SystemID id): id_(id)
{
}

//GameCtrlSystem//

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

//AsteroidsSystem//

AsteroidsSystem::AsteroidsSystem(int numAsteroid, double width, double height): System(ecs::AsteroidSys),
	numAsteroids(numAsteroid), width_(width), height_(height)
{
}

AsteroidsSystem::~AsteroidsSystem()
{
}

void AsteroidsSystem::init()
{
	gameSys = mngr->getSystem<GameCtrlSystem>(ecs::GameCtrlSys);
	for (int i = 0; i < numAsteroids; i++) {
		createAsteroid();
	}
}

void AsteroidsSystem::update()
{
	if (gameSys->getGameState == GameState::RUNNING) {
		for (Entity* ast : mngr->getEntities()) {
			if (ast->hasGroup(ecs::AsteroidsGroup)) {
				ast->update();
			}
		}

		if (sdlutils().currRealTime() - lastTime_ >= time_) {
			lastTime_ = sdlutils().currRealTime();
			createAsteroid();
		}
	}
}

void AsteroidsSystem::createAsteroid()
{
	int rnd = sdlutils().rand().nextInt(0, 10);
	int nGen = sdlutils().rand().nextInt(1, 4);
	if (rnd > 3) { // tipo A
		Entity* a = mngr->addEntity();

		Vector2D pos = Vector2D();
		pos.setX(sdlutils().rand().nextInt(0, sdlutils().width()));
		pos.setY(sdlutils().rand().nextInt(0, sdlutils().height()));

		Vector2D c = Vector2D();
		c.setX(sdlutils().rand().nextInt(0, sdlutils().width()));
		c.setY(sdlutils().rand().nextInt(0, sdlutils().height()));

		Vector2D vel = (c - pos).normalize() * (sdlutils().rand().nextInt(1, 10) / 10.0);

		a->addComponent<Transform>(pos, vel, 5 + nGen * width_, 5 + nGen * height_, sdlutils().rand().nextInt(0, 360));
		a->addComponent<FramedImage>(&sdlutils().images().at("AsteroidImg"), 5, 6, 0, 0, 600);
		a->addComponent<ShowAtOppositeSide>(sdlutils().width(), sdlutils().height());
		a->addComponent<Generations>(nGen);
		a->setGroup(ecs::AsteroidsGroup, true);
	}
	else {
		Entity* b = mngr->addEntity();

		Vector2D pos = Vector2D(sdlutils().rand().nextInt(0, sdlutils().width()), sdlutils().rand().nextInt(0, sdlutils().height()));

		Vector2D c = Vector2D();
		c.setX(sdlutils().rand().nextInt(0, sdlutils().width()));
		c.setY(sdlutils().rand().nextInt(0, sdlutils().height()));

		Vector2D vel = (c - pos).normalize() * (sdlutils().rand().nextInt(1, 10) / 10.0);

		b->addComponent<Transform>(pos, vel, 5 + nGen * width_, 5 + nGen * height_, sdlutils().rand().nextInt(0, 360));
		b->addComponent<FramedImage>(&sdlutils().images().at("AsteroidGoldenImg"), 5, 6, 0, 0, 600);
		b->addComponent<ShowAtOppositeSide>(sdlutils().width(), sdlutils().height());
		b->addComponent<Generations>(sdlutils().rand().nextInt(1, 4));
		b->addComponent<Follow>();
		b->setGroup(ecs::AsteroidsGroup, true);
	}
}

//BulletsSystem//

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

//CollisionSystem//

CollisionSystem::CollisionSystem()
{
}

void CollisionSystem::init()
{
	fighterSys = mngr->getSystem<FighterSystem>(ecs::FighterSys);
	bulletSys = mngr->getSystem<BulletsSystem>(ecs::BulletSys);
	astSys = mngr->getSystem<AsteroidsSystem>(ecs::AsteroidSys);
}

void CollisionSystem::update()
{
	for (Entity* a : mngr->getEntities()) {
		if (a->hasGroup(ecs::AsteroidsGroup)) {
			for (Entity* b : mngr->getEntities()) {
				if (a != b && b->hasGroup(ecs::BulletsGroup)) {
					if (isOnCollision(a->getComponent<Transform>(ecs::Transform), b->getComponent<Transform>(ecs::Transform))) {
						bulletSys->onCollisionWithAsteroid(b, a);
					}
				}
			}
		}
	}

	Transform* fighterTr_ = mngr->getHandler(ecs::FighterHndlr)->getComponent<Transform>(ecs::Transform);
	Health* health_ = mngr->getHandler(ecs::FighterHndlr)->getComponent<Health>(ecs::Health);
	
	for (Entity* a : mngr->getEntities()) {
		if (a->hasGroup(ecs::AsteroidsGroup)) {
			if (isOnCollision(a->getComponent<Transform>(ecs::Transform), fighterTr_)) {
				if (health_->getNumVidas() > 0) {

					
				}
				else {
					
				}
				
			}
		}
	}


}

bool CollisionSystem::isOnCollision(Transform* tA, Transform* tB)
{
	return (Collisions::collidesWithRotation(tA->getPos(), tA->getW(), tA->getH(), tA->getRotation(), tB->getPos(), tB->getW(), tB->getH(), tB->getRotation()));
}

//FighterGunSystem//

FighterGunSystem::FighterGunSystem(): System(ecs::FighterGunSys)
{
}

FighterGunSystem::~FighterGunSystem()
{
}

void FighterGunSystem::init()
{
	//bulletSys = mngr->getSystem<BulletsSystem>(ecs::BulletSys);
	//assert(bulletSys != nullptr);
}

void FighterGunSystem::update()
{
	//auto& ih = *InputHandler::instance();
	//if (ih.isKeyDown(SDLK_SPACE) && sdlutils().currRealTime() - lastTime_ >= time_) {
	//	bulletSys->shoot(Vector2D(),Vector2D(), 10,10);
	//}
}

//RenderSystem//

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

//FighterSystem//

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
	//Entity* fighter = mngr->addEntity();
	//fighter->addComponent<Transform>(Vector2D((sdlutils().width / 2) - 75, (sdlutils().height / 2) - 75), 150, 150, 0);
	//fighter->addComponent<ShowAtOppositeSide>(sdlutils().width, sdlutils().height());
	//fighter->addComponent<FighterCtrl>(0.5);
	//fighter->addComponent<DeAcceleration>(0.995);
	//fighter->addComponent<Health>(3);
	//
	//mngr->setHandler(fighter, ecs::FighterHndlr);
	//fighter->setGroup(ecs::Fighter, true);
	//
	//gameSys = mngr->getSystem<GameCtrlSystem>(ecs::GameCtrlSys);
}

void FighterSystem::update()
{
	//for (Entity* fighter : mngr->getEntities()) {
	//	if (fighter->hasGroup(ecs::Fighter)) {
	//		fighter->update();
	//	}
	//}
}
