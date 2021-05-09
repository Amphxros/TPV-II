#include "System.h"
#include "Manager.h"
#include "sdlutils/InputHandler.h"

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
	Health* health_ = mngr->getHandler(ecs::FighterHndlr)->getComponent<Health>(ecs::Health);
	if (health_->getNumVidas() > 0) {
		gs = GameState::PAUSED;
	}
	else {
		gs = GameState::GAMEOVER;
		health_->resetNumVidas();
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

//AsteroidsSystem//

AsteroidsSystem::AsteroidsSystem(int numAsteroid, double width, double height): 
	System(ecs::AsteroidSys),numAsteroids(numAsteroid), width_(width), height_(height), time_(500), lastTime_(0)
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
	if (gameSys->getGameState() == GameState::RUNNING) {
		for (Entity* ast : mngr->getEntities()) {
			if (ast->hasGroup(ecs::AsteroidsGroup)) {
				ast->update();
			}
		}

		if (sdlutils().currRealTime() - lastTime_ >= time_) {
			
			lastTime_ = sdlutils().currRealTime();
			createAsteroid();
			numAsteroids++;
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

void AsteroidsSystem::OnCollisionWithBullet(Entity* A){
	
	Transform* t = A->getComponent<Transform>(ecs::Transform);

	Generations* gen = A->getComponent<Generations>(ecs::Generations);
	Follow* f = A->getComponent<Follow>(ecs::Follow);
	int curr_gen = gen->getGen();

	if (curr_gen > 0) {

		Entity* astA = mngr->addEntity();
		astA->addComponent<Transform>(t->getPos(), t->getVel(), 5 + (curr_gen - 1) * width_, 5 + (curr_gen - 1) * height_, sdlutils().rand().nextInt(0, 360));
		if (f != nullptr) {
			astA->addComponent<FramedImage>(&sdlutils().images().at("AsteroidGoldenImg"), 5, 6, 0, 0, 600);
			astA->addComponent<Follow>();
		}
		else {
			astA->addComponent<FramedImage>(&sdlutils().images().at("AsteroidImg"), 5, 6, 0, 0, 600);
		}
		astA->addComponent<ShowAtOppositeSide>(sdlutils().width(), sdlutils().height());
		astA->addComponent<Generations>(curr_gen - 1);
		astA->setGroup(ecs::AsteroidsGroup, true);

		Vector2D p = astA->getComponent<Transform>(ecs::Transform)->getPos();
		Vector2D v = astA->getComponent<Transform>(ecs::Transform)->getVel();
		double w = A->getComponent<Transform>(ecs::Transform)->getW();
		double h = A->getComponent<Transform>(ecs::Transform)->getH();
		int r = astA->getComponent<Transform>(ecs::Transform)->getRotation();

		p.set(p + v.rotate(r) * 2 * w);
		v.set(v.rotate(r) * 1.1f);

		astA->setGroup(ecs::AsteroidsGroup, true);


		Entity* astB = mngr->addEntity();
		astB->addComponent<Transform>(t->getPos(), t->getVel(), 5 + (curr_gen - 1) * width_, 5 + (curr_gen - 1) * height_, sdlutils().rand().nextInt(0, 360));
		if (f != nullptr) {
			astB->addComponent<FramedImage>(&sdlutils().images().at("AsteroidGoldenImg"), 5, 6, 0, 0, 60);
			astB->addComponent<Follow>();
		}
		else {
			astB->addComponent<FramedImage>(&sdlutils().images().at("AsteroidImg"), 5, 6, 0, 0, 60);
		}
		astB->addComponent<ShowAtOppositeSide>(sdlutils().width(), sdlutils().height());
		astB->addComponent<Generations>(curr_gen - 1);
		astB->setGroup(ecs::AsteroidsGroup, true);

		p = astB->getComponent<Transform>(ecs::Transform)->getPos();
		v = astB->getComponent<Transform>(ecs::Transform)->getVel();
		w = A->getComponent<Transform>(ecs::Transform)->getW();
		h = A->getComponent<Transform>(ecs::Transform)->getH();
		r = astB->getComponent<Transform>(ecs::Transform)->getRotation();

		p.set(p - v.rotate(r) * 2 * w);
		v.set(v.rotate(r * 1.1f));

		astB->setGroup(ecs::AsteroidsGroup, true);
	numAsteroids+=1;
	}
	else{
		numAsteroids--;
		if(numAsteroids<=0){
			gameSys->onAsteroidsExtinction();
		}
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
	e->addComponent<Image>(&sdlutils().images().at("Bullet"));
	e->addComponent<DisableOnExit>(sdlutils().width(), sdlutils().height());
	e->setGroup(ecs::BulletsGroup, true);
	mngr->setHandler(e, ecs::BulletsHndlr);
}

void BulletsSystem::onCollisionWithAsteroid(Entity* b, Entity* a)
{
	b->setActive(false);

}

//CollisionSystem//

CollisionSystem::CollisionSystem()
{
}

void CollisionSystem::init()
{
	gameSys = mngr->getSystem<GameCtrlSystem>(ecs::GameCtrlSys);
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
						astSys->OnCollisionWithBullet(a);
						a->setActive(false);
					}
				}
			}
		}
	}

	Transform* fighterTr_ = mngr->getHandler(ecs::FighterHndlr)->getComponent<Transform>(ecs::Transform);

	for (Entity* a : mngr->getEntities()) {
		if (a->hasGroup(ecs::AsteroidsGroup)) {
			if (isOnCollision(a->getComponent<Transform>(ecs::Transform), fighterTr_)) {
				fighterSys->onCollisionWithAsteroid(a);
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
		Transform* tr_ = mngr->getHandler(ecs::FighterHndlr)->getComponent<Transform>(ecs::Transform);
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
	mngr->getHandler(ecs::FighterHndlr)->render();

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
	a->setActive(false);
	Health* h =fighter->getComponent<Health>(ecs::Health);
	h->setNumVidas(h->getNumVidas() - 1);
	fighter->getComponent<Transform>(ecs::Transform)->setPos(sdlutils().width() / 2, sdlutils().height() / 2);
	fighter->getComponent<Transform>(ecs::Transform)->setVel(0, 0);
	fighter->getComponent<Transform>(ecs::Transform)->setRotation(0);

	gameSys->onFighterDeath();
}

void FighterSystem::init()
{
	fighter = mngr->addEntity();
	fighter->addComponent<Transform>(Vector2D(sdlutils().width() / 2, sdlutils().height() / 2),Vector2D(), 50, 50, 0);
	fighter->addComponent<Image>(&sdlutils().images().at("fighter"));
	fighter->addComponent<ShowAtOppositeSide>(sdlutils().width(), sdlutils().height());
	fighter->addComponent<FighterCtrl>(0.5);
	fighter->addComponent<DeAcceleration>(0.995);
	fighter->addComponent<Health>(3);
	
	mngr->setHandler(fighter, ecs::FighterHndlr);
	fighter->setGroup(ecs::Fighter, true);
	
	gameSys = mngr->getSystem<GameCtrlSystem>(ecs::GameCtrlSys);
}

void FighterSystem::update()
{
	for (Entity* fighter : mngr->getEntities()) {
		if (fighter->hasGroup(ecs::Fighter) && gameSys->getGameState() == GameState::RUNNING) {
			fighter->update();
		}
	}
}
