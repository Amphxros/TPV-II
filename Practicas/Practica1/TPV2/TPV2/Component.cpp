#include "Component.h"
#include "Entity.h"
#include "Manager.h"
#include "sdlutils/InputHandler.h"

//COMPONENTE TRANSFORM
Transform::Transform() :
	Component(ecs::Transform), pos_(Vector2D()), vel_(Vector2D()), w_(0), h_(0), rot_(0)
{
}

Transform::Transform(Vector2D pos, Vector2D vel, double width, double height, double rotation) :
	Component(ecs::Transform), pos_(pos), vel_(vel), w_(width), h_(height), rot_(rotation)
{
}

void Transform::update()
{
	pos_ = pos_ + vel_;
}


//DEACCELERATION
DeAcceleration::DeAcceleration(double deAcceleration) :
	Component(ecs::DeAcceleration), tr_(nullptr), deAccel_(deAcceleration)
{
}

DeAcceleration::~DeAcceleration()
{
	tr_ = nullptr;
}

void DeAcceleration::init()
{
	tr_ = entity_->getComponent<Transform>(ecs::Transform);
	assert(tr_ != nullptr);
}

void DeAcceleration::update()
{
	Vector2D vel = tr_->getVel() * deAccel_;
	tr_->setVel(vel);
}



//COMPONENTE IMAGE
Image::Image(Texture* t) :
	Component(ecs::Image), texture_(t), tr_(nullptr)
{
}

void Image::init()
{
	tr_ = entity_->getComponent<Transform>(ecs::Transform);
	assert(tr_ != nullptr);
}

void Image::render()
{
	SDL_Rect dest;
	dest.x = tr_->getPos().getX();
	dest.y = tr_->getPos().getY();
	dest.w = tr_->getW();
	dest.h = tr_->getH();

	texture_->render(dest, tr_->getRotation());
	assert(tr_ != nullptr && texture_ != nullptr);
}


//COMPONETE HEALTH
Health::Health():Component(ecs::Health), maxVidas_(3), texture_(nullptr), num_(3)
{
}
Health::Health(int num) :
	Component(ecs::Health), maxVidas_(num), texture_(nullptr), num_(num)
{
	std::cout << getNumVidas() << std::endl;
}
void Health::init()
{
	texture_ = &sdlutils().images().at("fighter");
}

void Health::render()
{
	for (int i = 0; i < num_; i++) {

		SDL_Rect dest;
		dest.x = sdlutils().width() / 3;
		dest.y = 50;
		dest.w = 50;
		dest.y = 50;

		texture_->render(dest);
	}
}

//COMPONENTE GUN
Gun::Gun() :
	time_(0), Component(ecs::Gun), tr_(nullptr), mngr_(nullptr), curr_time_(0)
{
}

Gun::Gun(uint32_t time) :
	Component(ecs::Gun), time_(time), tr_(nullptr), mngr_(nullptr),curr_time_(0)
{
}

void Gun::init()
{
	curr_time_ = sdlutils().currRealTime() - time_;
	mngr_ = entity_->getMngr();
	tr_ = entity_->getComponent<Transform>(ecs::Transform);
	assert(tr_ != nullptr);
}

void Gun::update()
{
	auto& ih = *InputHandler::instance();
	if (ih.isKeyDown(SDLK_SPACE)) {
		curr_time_ = sdlutils().currRealTime();

		Entity* b = mngr_->addEntity();
	
		Vector2D pos = tr_->getPos() + Vector2D(tr_->getW() / 2.0f, tr_->getH() / 2.0f) - Vector2D(0.0f, tr_->getH() / 2.0f + 7.0f).rotate(tr_->getRotation()) - Vector2D(2.0f, 10.0f);

		Vector2D v = Vector2D(0, -1).rotate(tr_->getRotation()) * (tr_->getVel().magnitude() + 5.0f);

		b->addComponent<Transform>(pos, v, 5, 5, tr_->getRotation());
		b->addComponent <Image>(&sdlutils().images().at("Bullet"));
		b->addComponent<DisableOnExit>(sdlutils().width(), sdlutils().height());
		b->setGroup(ecs::BulletsGroup,true);
		mngr_->setHandler(b, ecs::BulletsHndlr);
	}
}


//COMPONENTE FIGHTERCTRL
FighterCtrl::FighterCtrl() :
	Component(ecs::FighterCtrl), tr_(nullptr), thrust_(0)
{
}

FighterCtrl::FighterCtrl(double thrust):
	Component(ecs::FighterCtrl), tr_(nullptr), thrust_(thrust)
{
}

void FighterCtrl::init()
{
	tr_ = entity_->getComponent<Transform>(ecs::Transform);
	pos_ini = tr_->getPos();
	assert(tr_ != nullptr);
	sdlutils().soundEffects().at("gunshot").play();

}

void FighterCtrl::update()
{
	auto& ih = *InputHandler::instance();
	if (ih.isKeyDown(SDLK_UP)) {
		Vector2D vel = tr_->getVel();
		Vector2D newVel = vel + Vector2D(0, -1).rotate(tr_->getRotation()) * thrust_; 
		
		tr_->setVel(newVel);
	}
	else if (ih.isKeyDown(SDLK_LEFT)) {
		double r = tr_->getRotation() - 5.0;
		
		tr_->setRotation(r);
	}
	else if (ih.isKeyDown(SDLK_RIGHT)) {
		double r = tr_->getRotation() + 5.0;
		
		tr_->setRotation(r);
	}
	else if (ih.isKeyDown(SDLK_DOWN)) {
		Vector2D vel = tr_->getVel();
		Vector2D newVel = vel + Vector2D(0, 1).rotate(tr_->getRotation()) * thrust_; 
		tr_->setVel(newVel);
	}
}

void FighterCtrl::resetPos()
{
	tr_->setPos(pos_ini);
	tr_->setVel(Vector2D());
}


//COMPONENTE SHOW AT OPPOSITE SIDE
ShowAtOppositeSide::ShowAtOppositeSide() : 
	Component(ecs::ShowAtOppositeSide), tr_(nullptr), width_(0), height_(0)
{
}

ShowAtOppositeSide::ShowAtOppositeSide(int width, int height) :
	Component(ecs::ShowAtOppositeSide), width_(width), height_(height), tr_(nullptr)
{
}

void ShowAtOppositeSide::init()
{
	tr_ = entity_->getComponent<Transform>(ecs::Transform);
	assert(tr_ != nullptr);
}

void ShowAtOppositeSide::update()
{
	//comprobamos en X
	if (tr_->getPos().getX() < 0) {
		tr_->setPos(Vector2D(width_, tr_->getPos().getY()));
	}
	else if (tr_->getPos().getX() > width_) {

		tr_->setPos(Vector2D(tr_->getW(), tr_->getPos().getY()));
	}
	// comprobamos en y
	if (tr_->getPos().getY() < 0) {

		tr_->setPos(Vector2D(tr_->getPos().getX(), height_));
	}
	else if (tr_->getPos().getY() > height_) {

		tr_->setPos(Vector2D(tr_->getPos().getX(), tr_->getH()));
	}
}

FramedImage::FramedImage(Texture* texture, int nRows, int nCols, int posX, int posY, float framerate) :
	Component(ecs::FramedImage), texture_(texture), nRows_(nRows), nCols_(nCols), framerate_(framerate),pos_X(posX), pos_Y(posY), tr_(nullptr)
{
	width = texture_->width() / nCols_;
	height = texture_->height() / nRows_;

	src_.x = pos_X * width;
	src_.y = pos_Y * height;
	src_.w = width;
	src_.h = height;

	tam = Vector2D(nCols_, nRows_);
	ini = Vector2D(pos_X, pos_Y);

}

FramedImage::~FramedImage()
{
}

void FramedImage::init()
{
	tr_ = entity_->getComponent<Transform>(ecs::Transform);
	assert(tr_ != nullptr);
}

void FramedImage::render()
{
	SDL_Rect dest;
	dest.x = tr_->getPos().getX();
	dest.y = tr_->getPos().getY();
	dest.w = tr_->getW();
	dest.h = tr_->getH();

	texture_->render(src_, dest, tr_->getRotation());

}

void FramedImage::update()
{

}

Generations::Generations():
	maxgen_(0),gen_(0)
{
}

Generations::Generations(int gen): 
	Component(ecs::Generations), maxgen_(gen), gen_(gen)
{
}

void Generations::resetGen()
{
	gen_ = maxgen_;
}


DisableOnExit::DisableOnExit(int width, int height): 
	Component(ecs::DisableOnExit), width_(width), height_(height), tr_(nullptr)
{
}

DisableOnExit::~DisableOnExit()
{
}

void DisableOnExit::init()
{
	tr_ = entity_->getComponent<Transform>(ecs::Transform);
	assert(tr_ != nullptr);
}

void DisableOnExit::update()
{
	bool b = false;
	//comprobamos en X
	if (tr_->getPos().getX() < 0) {
		b = true;
	}
	else if (tr_->getPos().getX() > width_) {
		b = true;
	}
	// comprobamos en y
	if (tr_->getPos().getY() < 0) {
		b = true;
	}
	else if (tr_->getPos().getY() > height_) {
		b = true;
	}

	if (b)
		entity_->setActive(false);
}



AsteroidsManager::AsteroidsManager(): 
	Component(ecs::AsteroidsManager), num_asteroids(0), time_(0), width_(0), height_(0), gen_(0), lastTime_(0), mngr_(nullptr),state_(nullptr)
{
}

AsteroidsManager::AsteroidsManager(int numAsteroids, int time, int width, int height) :
	Component(ecs::AsteroidsManager), num_asteroids(numAsteroids), time_(time), width_(width), height_(height), gen_(0), lastTime_(0), mngr_(nullptr),state_(nullptr)
{
}

void AsteroidsManager::init()
{
	mngr_ = entity_->getMngr();
	state_ = entity_->getComponent<State>(ecs::State);
	assert(state_ != nullptr);
}

void AsteroidsManager::update()
{
	if (sdlutils().currRealTime() - lastTime_ >= time_ && gen_ > 0 ) {
		lastTime_ = sdlutils().currRealTime();
		gen_ = sdlutils().rand().nextInt(1, 4);
		if(state_!=nullptr && state_->isGameRunning())
			createAsteroid(gen_);
	}
}

void AsteroidsManager::createAsteroids()
{
	for (int i = 0; i < num_asteroids; i++) {
		gen_ = sdlutils().rand().nextInt(1, 4);
		createAsteroid(gen_);
	}
}

void AsteroidsManager::createAsteroid(int nGen)
{
	// 70% A, 30% B
	int rnd= sdlutils().rand().nextInt(0, 10);
	if (rnd > 3) { // tipo A
		Entity* a = mngr_->addEntity();

		Vector2D pos = Vector2D();
		pos.setX(sdlutils().rand().nextInt(0, sdlutils().width()));
		pos.setY(sdlutils().rand().nextInt(0, sdlutils().height()));

		Vector2D vel = Vector2D();
		vel.setX(sdlutils().rand().nextInt(-5,5));
		vel.setY(sdlutils().rand().nextInt(-5, 5));

		a->addComponent<Transform>(pos, vel, 5+ nGen * width_, 5+ nGen * height_, sdlutils().rand().nextInt(0, 360));
		a->addComponent<FramedImage>(&sdlutils().images().at("AsteroidImg"), 5, 6, 0, 0, 60);
		a->addComponent<ShowAtOppositeSide>(sdlutils().width(), sdlutils().height());
		a->addComponent<Generations>(nGen);
		a->setGroup(ecs::AsteroidsGroup, true);
	}
	else {
		Entity* b = mngr_->addEntity();

		Vector2D pos = Vector2D(sdlutils().rand().nextInt(0, sdlutils().width()), sdlutils().rand().nextInt(0, sdlutils().height()));
		Vector2D vel = Vector2D(sdlutils().rand().nextInt(-5, 5), sdlutils().rand().nextInt(-5, 5));

		b->addComponent<Transform>(pos, vel, 5 + nGen * width_, 5 + nGen * height_, sdlutils().rand().nextInt(0, 360));
		b->addComponent<FramedImage>(&sdlutils().images().at("AsteroidGoldenImg"), 5, 6, 0, 0, 60);
		b->addComponent<ShowAtOppositeSide>(sdlutils().width(), sdlutils().height());
		b->addComponent<Generations>(sdlutils().rand().nextInt(1, 4));
		b->addComponent<Follow>();
		b->setGroup(ecs::AsteroidsGroup, true);
	}

}

void AsteroidsManager::OnCollision(Entity* A) {

	Transform* t = A->getComponent<Transform>(ecs::Transform);

	Generations* gen = A->getComponent<Generations>(ecs::Generations);
	Follow* f = A->getComponent<Follow>(ecs::Follow);
	int curr_gen = gen->getGen();

	if (curr_gen > 0) {
		
		Entity* astA = mngr_->addEntity();
		astA->addComponent<Transform>(t->getPos(), t->getVel(), 5 + (curr_gen - 1) * width_, 5 + (curr_gen - 1) * height_, sdlutils().rand().nextInt(0, 360));
		if (f != nullptr) {
			astA->addComponent<FramedImage>(&sdlutils().images().at("AsteroidGoldenImg"), 5, 6, 0, 0, 60);
			astA->addComponent<Follow>();
		}
		else {
			astA->addComponent<FramedImage>(&sdlutils().images().at("AsteroidImg"), 5, 6, 0, 0, 60);
		}
		astA->addComponent<ShowAtOppositeSide>(sdlutils().width(), sdlutils().height());
		astA->addComponent<Generations>(curr_gen-1);
		astA->setGroup(ecs::AsteroidsGroup, true);
		
		Vector2D p = astA->getComponent<Transform>(ecs::Transform)->getPos();
		Vector2D v = astA->getComponent<Transform>(ecs::Transform)->getVel();
		double w = astA->getComponent<Transform>(ecs::Transform)->getW();
		double h = astA->getComponent<Transform>(ecs::Transform)->getH();
		int r = sdlutils().rand().nextInt(0, 360);
		
		p.set(p + v.rotate(r) * 2 * w);
		v.set(v.rotate(r) * 1.1f);
		
		astA->setGroup(ecs::AsteroidsGroup,true);
		
		
		Entity* astB = mngr_->addEntity();
		astB->addComponent<Transform>(t->getPos(), t->getVel(), 5 + (curr_gen - 1) * width_, 5 + (curr_gen - 1) * height_, sdlutils().rand().nextInt(0, 360));
		if (f != nullptr) {
			astB->addComponent<FramedImage>(&sdlutils().images().at("AsteroidGoldenImg"), 5, 6, 0, 0, 60);
			astB->addComponent<Follow>();
		}
		else {
			astB->addComponent<FramedImage>(&sdlutils().images().at("AsteroidImg"), 5, 6, 0, 0, 60);
		}
		astB->addComponent<ShowAtOppositeSide>(sdlutils().width(), sdlutils().height());
		astB->addComponent<Generations>(curr_gen-1);
		astB->setGroup(ecs::AsteroidsGroup, true);

		p = astB->getComponent<Transform>(ecs::Transform)->getPos();
		v = astB->getComponent<Transform>(ecs::Transform)->getVel();
		w = astB->getComponent<Transform>(ecs::Transform)->getW();
		h = astB->getComponent<Transform>(ecs::Transform)->getH();
		r = sdlutils().rand().nextInt(0, 360);

		p.set(p - v.rotate(r) * 2 * w);
		v.set(v.rotate(r) * 1.1f);

		astB->setGroup(ecs::AsteroidsGroup,true);
	}
	
}



Follow::Follow(): 
	Component(ecs::Follow), tr_(nullptr), posPlayer(nullptr)
{
}

void Follow::init()
{
	tr_ = entity_->getComponent<Transform>(ecs::Transform);
	assert(tr_ != nullptr);
	posPlayer = entity_->getMngr()->getHandler(ecs::FighterHndlr)->getComponent<Transform>(ecs::Transform);
	assert(posPlayer != nullptr);
}

void Follow::update()
{
	auto dir = tr_->getVel();
	Vector2D pos_ = tr_->getPos();
	dir.set(dir.rotate(dir.angle(posPlayer->getPos() - pos_) > 0 ? 1.0f : -1.0f));
	
	tr_->setVel(dir);
}

CollisionsManager::CollisionsManager(): 
	Component(ecs::CollisionsManager),
	ast(nullptr), fighter_(nullptr), health_(nullptr),state_(nullptr),fighterTr_(nullptr)
{
}

void CollisionsManager::init()
{
	ast = entity_->getComponent<AsteroidsManager>(ecs::AsteroidsManager);
	fighter_ = entity_->getMngr()->getHandler(ecs::FighterHndlr);
	fighterTr_ = entity_->getMngr()->getHandler(ecs::FighterHndlr)->getComponent<Transform>(ecs::Transform);
	health_ = fighter_->getComponent<Health>(ecs::Health);
	state_ = entity_->getComponent<State>(ecs::State);
}

void CollisionsManager::update()
{
	auto entities = entity_->getMngr()->getEntities();
	
	for (Entity* a : entities) {
		if (a->hasGroup(ecs::AsteroidsGroup)) {
			for (Entity* b : entities) {
				if (a != b && b->hasGroup(ecs::BulletsGroup)) {
					if (isOnCollision(a->getComponent<Transform>(ecs::Transform), b->getComponent<Transform>(ecs::Transform))) {
						ast->OnCollision(a);
						a->setActive(false);
						b->setActive(false);
					}
				}
			}
		}
	}

	for (Entity* a : entities) {
		if (a->hasGroup(ecs::AsteroidsGroup)) {
			if (isOnCollision(a->getComponent<Transform>(ecs::Transform), fighterTr_)) {
				if (health_->getNumVidas() > 0) {

					state_->setState(State::GameState::PAUSED);	
					health_->setNumVidas(health_->getNumVidas() - 1);
				}
				else {
					state_->setState(State::GameState::GAMEOVER);
					health_->resetNumVidas();
				}
				fighter_->getComponent<FighterCtrl>(ecs::FighterCtrl)->resetPos();
				entity_->getMngr()->resetGame();
				a->setActive(false);
			}
		}
	}

}

bool CollisionsManager::isOnCollision(Transform* tA, Transform* tB)
{
	return (Collisions::collidesWithRotation(tA->getPos(), tA->getW(), tA->getH(), tA->getRotation(), tB->getPos(), tB->getW(), tB->getH(), tB->getRotation()));
}

State::State(): 
	Component(ecs::State),gs(GameState::NEWGAME), startMsg(nullptr), continueMsg(nullptr), gameOverMsg(nullptr)
{
}

State::~State()
{
	delete startMsg;	startMsg = nullptr;
	delete continueMsg; continueMsg= nullptr;
	delete gameOverMsg; gameOverMsg= nullptr;
}

void State::init()
{
	startMsg = &sdlutils().msgs().at("Start");
	continueMsg = &sdlutils().msgs().at("Continue");
	gameOverMsg = &sdlutils().msgs().at("gameOver");

}

void State::render()
{
	SDL_Rect dest;
	switch (gs)
	{
	case State::NEWGAME:
		dest.x = sdlutils().width() / 3;
		dest.y = sdlutils().height() / 2;
		dest.w = startMsg->width();
		dest.h = startMsg->height();

		startMsg->render(dest);
		break;

	case State::PAUSED:
		dest.x = sdlutils().width() / 4;
		dest.y = sdlutils().height() / 2;
		dest.w = continueMsg->width();
		dest.h = continueMsg->height();

		continueMsg->render(dest);
		break;

	case State::GAMEOVER:
		dest.x = sdlutils().width() / 4;
		dest.y = sdlutils().height() / 2;
		dest.w = gameOverMsg->width();
		dest.h = gameOverMsg->height();
		
		gameOverMsg->render(dest);
		break;
	}
}

GameCtrl::GameCtrl():
	Component(ecs::GameCtrl), state_(nullptr), astManager_(nullptr),mngr_(nullptr)
{
}

void GameCtrl::init()
{
	state_ = entity_->getComponent<State>(ecs::State);
	astManager_ = entity_->getComponent<AsteroidsManager>(ecs::AsteroidsManager);
	mngr_ = entity_->getMngr();
}

void GameCtrl::update()
{
	auto& ih = *InputHandler::instance();
	if (ih.keyDownEvent()) {
		if (state_->isGameNew()) {
			state_->setState(State::GameState::RUNNING);
			astManager_->createAsteroids();
		}
		else if (state_->isGameOver()) {
			state_->setState(State::GameState::NEWGAME);
		}	
		if (state_->isGameRunning() && ih.isKeyDown(SDLK_SPACE)) {
			state_->setState(State::GameState::PAUSED);
		
		}
		if (state_->isGamePaused() && ih.isKeyDown(SDLK_SPACE)) {
			state_->setState(State::GameState::RUNNING);
		}

	}
}