#include "System.h"
#include "Manager.h"
#include "sdlutils/InputHandler.h"
#include "NetworkSystem.h"

//System//

System::System(): id_(),mngr(nullptr){}

System::System(ecs::SystemID id) : id_(id), mngr(nullptr) {}

void System::setManager(Manager* m){
	mngr = m; 
	mngr->addSystem(this, id_); 
}

//GameCtrlSystem//

GameCtrlSystem::GameCtrlSystem(): 
	System(ecs::GameCtrlSys), gs(GameState::NEW), msgInit(nullptr), msgGameOver(nullptr), msgPause(nullptr)
{
}

GameCtrlSystem::~GameCtrlSystem()
{
	delete msgInit;
	delete msgPause;
	delete msgGameOver;
}

void GameCtrlSystem::onFighterDeath()
{
	Health* health_A = mngr->getHandler(ecs::FighterAHndlr)->getComponent<Health>(ecs::Health);
	Health* health_B = mngr->getHandler(ecs::FighterBHndlr)->getComponent<Health>(ecs::Health);
	
	if (health_A->getNumVidas() > 0 && health_B->getNumVidas()>0) {
		gs = GameState::PAUSED;
	}
	else {
		gs = GameState::GAMEOVER;
		health_A->resetNumVidas();
		health_B->resetNumVidas();
	}
	mngr->resetGame();
}

void GameCtrlSystem::onAsteroidsExtinction()
{
	gs = GameState::GAMEOVER;
	mngr->resetGame();
}

void GameCtrlSystem::init()
{
	msgInit = &(sdlutils().msgs().at("Start"));
	msgPause = &(sdlutils().msgs().at("Continue"));
	msgGameOver = &(sdlutils().msgs().at("gameOver"));
}

void GameCtrlSystem::update()
{
	SDL_Rect dest;
	auto ih = InputHandler::instance();
	if (gs == GameState::NEW) {
		dest.x = sdlutils().width() / 3;
		dest.y = sdlutils().height() / 2;
		dest.w = msgInit->width();
		dest.h = msgInit->height();

		msgInit->render(dest);
		if (ih->isKeyDown(SDLK_SPACE)) {
			gs = GameState::RUNNING;
		}
	}
	else if (gs == GameState::PAUSED) {
		
		dest.x = sdlutils().width() / 3;
		dest.y = sdlutils().height() / 2;
		dest.w = msgPause->width();
		dest.h = msgPause->height();
		msgPause->render(dest);
		if (ih->isKeyDown(SDLK_SPACE)) {
			gs = GameState::RUNNING;
		}
	}
	else if (gs == GameState::GAMEOVER) {
		
		dest.x = sdlutils().width() / 3;
		dest.y = sdlutils().height() / 2;
		dest.w = msgGameOver->width();
		dest.h = msgGameOver->height();
		msgGameOver->render(dest);
		if (ih->isKeyDown(SDLK_SPACE)) {
			gs = GameState::NEW;
		}
	}
	else {
		if (ih->isKeyDown(SDLK_SPACE)) {
			gs = GameState::PAUSED;
		}
	}
}


//BulletsSystem//

BulletsSystem::BulletsSystem(): System(ecs::BulletSys), gameSys_(nullptr), networkSys_(nullptr)
{
}

BulletsSystem::~BulletsSystem()
{
}

void BulletsSystem::init()
{
	gameSys_ = mngr->getSystem<GameCtrlSystem>(ecs::GameCtrlSys);
	networkSys_ = mngr->getSystem<NetworkSystem>(ecs::NetWorkSys);
}

void BulletsSystem::update()
{
	for (auto b : mngr->getEntities()) {
		if (b->hasGroup(ecs::BulletsGroup) && gameSys_->getGameState()==GameState::RUNNING) {
			b->update();
		}
	}
}

void BulletsSystem::shoot(Vector2D pos, Vector2D vel, double width, double height)
{
	Entity* e = mngr->addEntity();
	e->addComponent<Transform>(pos, vel, width, height, vel.angle(Vector2D(0.0f, 1.0f)));
	e->addComponent<Image>(&sdlutils().images().at("Bullet"));
	e->addComponent<DisableOnExit>(sdlutils().width(), sdlutils().height());
	e->setGroup(ecs::BulletsGroup, true);
	mngr->setHandler(e, ecs::BulletsHndlr);

	networkSys_->sendBulletInfo(pos, vel);

}

void BulletsSystem::onCollisionWithAsteroid(Entity* b, Entity* a)
{
	b->setActive(false);

}

//CollisionSystem//

CollisionSystem::CollisionSystem(): 
	System(ecs::CollisionSys), gameSys(nullptr), fighterSys(nullptr)
{
}

void CollisionSystem::init()
{
	gameSys = mngr->getSystem<GameCtrlSystem>(ecs::GameCtrlSys);
	fighterSys = mngr->getSystem<FighterSystem>(ecs::FighterSys);
	bulletSys = mngr->getSystem<BulletsSystem>(ecs::BulletSys);

}

void CollisionSystem::update()
{
	
	Transform* fighterATr_ = mngr->getHandler(ecs::FighterAHndlr)->getComponent<Transform>(ecs::Transform);
	Transform* fighterBTr_ = mngr->getHandler(ecs::FighterBHndlr)->getComponent<Transform>(ecs::Transform);
	
	//colisiones con balas
	for (Entity* b : mngr->getEntities()) {
		if (b->hasGroup(ecs::BulletsGroup)) {
			if (isOnCollision(b->getComponent<Transform>(ecs::Transform), fighterATr_)) {
				fighterSys->onCollisionWithAsteroid(b);
			}
			else if (isOnCollision(b->getComponent<Transform>(ecs::Transform), fighterBTr_)) {
				fighterSys->onCollisionWithAsteroid(b);
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
	bulletSys = mngr->getSystem<BulletsSystem>(ecs::BulletSys);
	gameSys = mngr->getSystem<GameCtrlSystem>(ecs::GameCtrlSys);
	assert(bulletSys != nullptr);
}

void FighterGunSystem::update()
{
	auto& ih = *InputHandler::instance();
	if (ih.isKeyDown(SDLK_s) && sdlutils().currRealTime() - lastTime_ >= time_ &&  gameSys->getGameState()==GameState::RUNNING) {
		lastTime_=time_;
		Transform* tr_ = mngr->getHandler(ecs::FighterAHndlr)->getComponent<Transform>(ecs::Transform);
		Vector2D pos = tr_->getPos();
		Vector2D vel = tr_->getVel();

		float r = tr_->getRotation();
		float w = tr_->getW();
		float h = tr_->getH();

		Vector2D bPos = pos + Vector2D(w / 2.0f, h / 2.0f) - Vector2D(0.0f, h / 2.0f + 5.0f + 12.0f).rotate(r) - Vector2D(2.0f, 10.0f);
		Vector2D bVel = Vector2D(0.0f, -1.0f).rotate(r) * (vel.magnitude() + 5.0f);

		bulletSys->shoot(bPos,bVel, 5,20);
	}
}

//RenderSystem//

RenderSystem::RenderSystem(): 
	System(ecs::RenderSys)
{
}

void RenderSystem::init()
{
}

void RenderSystem::update()
{
	for (auto e : mngr->getEntities()) {
		if (e->hasGroup(ecs::AsteroidsGroup)) {
			e->render();
		}
	}

	for (auto e : mngr->getEntities()) {
		if (e->hasGroup(ecs::BulletsGroup)) {
			e->render();
		}
	}
	mngr->getHandler(ecs::FighterAHndlr)->render();

}

//FighterSystem//

FighterSystem::FighterSystem():
	System(ecs::FighterSys)
{
}

FighterSystem::~FighterSystem()
{
}

void FighterSystem::onCollisionWithAsteroid(Entity* a)
{
	
	gameSys->onFighterDeath();
}

void FighterSystem::init()
{
	fighterA = mngr->addEntity();
	fighterA->addComponent<Transform>(Vector2D(sdlutils().width() / 4, sdlutils().height() / 2),Vector2D(), 50, 50, 90);
	fighterA->addComponent<Image>(&sdlutils().images().at("fighter"));
	fighterA->addComponent<ShowAtOppositeSide>(sdlutils().width(), sdlutils().height());
	fighterA->addComponent<FighterCtrl>(0.5);
	fighterA->addComponent<DeAcceleration>(0.995);
	fighterA->addComponent<Health>(3);
	
	mngr->setHandler(fighterA, ecs::FighterAHndlr);
	fighterA->setGroup(ecs::Fighter, true);
	
	fighterB = mngr->addEntity();
	fighterB->addComponent<Transform>(Vector2D(3* sdlutils().width() / 4, sdlutils().height() / 2),Vector2D(), 50, 50, 270);
	fighterB->addComponent<Image>(&sdlutils().images().at("fighter"));
	fighterB->addComponent<ShowAtOppositeSide>(sdlutils().width(), sdlutils().height());
	fighterB->addComponent<FighterCtrl>(0.5);
	fighterB->addComponent<DeAcceleration>(0.995);
	fighterB->addComponent<Health>(3);
	
	mngr->setHandler(fighterB, ecs::FighterBHndlr);
	fighterB->setGroup(ecs::Fighter, true);

	networkSys_ = mngr->getSystem<NetworkSystem>(ecs::NetWorkSys);
	gameSys = mngr->getSystem<GameCtrlSystem>(ecs::GameCtrlSys);
}

void FighterSystem::update()
{
	Uint8 mId_ = mngr->getSystem<NetworkSystem>(ecs::NetWorkSys)->getId();
	if (mId_ == 0) {
		MoveEntity(fighterA);
	}
	else {
		MoveEntity(fighterB);
	}

}

void FighterSystem::MoveEntity(Entity* e)
{
	e->update();
	networkSys_->sendFighterPosition(e->getComponent<Transform>(ecs::Transform)->getPos());

}
