#include "AsteroidsManager.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "State.h"
#include "Transform.h"

#include "Image.h"
#include "Follow.h"
#include "Generations.h"
#include "ShowAtOppositeSide.h"
#include "FramedImage.h"

AsteroidsManager::AsteroidsManager():
	Component(),initAsteroids(0) , numAsteroids(0), asteroidperTime(0), lastCreatedTime_(0),time_(0), mState_(nullptr)
{
}

AsteroidsManager::AsteroidsManager(double astPerTime, int initialAsteroids): 
	Component(), initAsteroids(initialAsteroids), asteroidperTime(astPerTime), mState_(nullptr), lastCreatedTime_(0), time_(0), numAsteroids(0)
{
}

AsteroidsManager::~AsteroidsManager()
{
}

void AsteroidsManager::init()
{
	mState_ = entity_->getComponent<State>();
	lastCreatedTime_ = sdlutils().currRealTime();
}

void AsteroidsManager::initGame(){
	numAsteroids = 0;
	for(int i=0;i<initAsteroids; i++){
		createAsteroid();	
	}

}

void AsteroidsManager::endGame(){
	numAsteroids = 0;
}

void AsteroidsManager::update()
{	
	// Actualiza solo si el juego está activo (No en pausa)
	if (mState_->getGameState() == GameState::RUNNING) {
	
		time_ = sdlutils().currRealTime();
		if (time_ - lastCreatedTime_ >= asteroidperTime) {
			createAsteroid();
			lastCreatedTime_ = sdlutils().currRealTime();
		}
	}
}

// Colision que elimina el asteroide o lo divide en funcion de su tipo
void AsteroidsManager::onCollisionWithBullet(Entity* a)
{
	int gen = a->getComponent<Generations>()->getGen();

	if (gen > 0) {
		//asteroide A
		Entity* a_ = entity_->getMngr()->addEntity();
		Vector2D p = a->getComponent<Transform>()->getPos();
		Vector2D v = a->getComponent<Transform>()->getDir();
		double r = a->getComponent<Transform>()->getRotation();
		double w = a->getComponent<Transform>()->getW();

		Vector2D pos = p + v.rotate(r) * 2 * w;
		Vector2D vel = v.rotate(r) * 1.1f;

		a_->addComponent<Transform>(pos, vel, 10 + 5 * gen - 1, 10 + 5 * gen - 1, sdlutils().rand().nextInt(0, 360));
		a_->addComponent<ShowAtOppositeSide>();
		a_->addComponent<Generations>(gen - 1);

		a_->setGroup<Asteroids>(true);

		//asteroide B
		Entity* b_ = entity_->getMngr()->addEntity();

		pos = p - v.rotate(r) * 2 * w;
		vel = v.rotate(-r) * 1.1f;

		b_->addComponent<Transform>(pos, vel, 10 + 5 * gen - 1, 10 + 5 * gen - 1, sdlutils().rand().nextInt(0, 360));
		b_->addComponent<ShowAtOppositeSide>();
		b_->addComponent<Generations>(gen - 1);
		b_->setGroup<Asteroids>(true);


		//si el asteroide es de tipo B sus hijos tambien lo son
		if (a->hasComponent<Follow>()) {
			a_->addComponent<Follow>();
			a_->addComponent<FramedImage>(&(sdlutils().images().at("asteroid_gold")), 5, 6, 0, 0, 50.0f);
			b_->addComponent<Follow>();
			b_->addComponent<FramedImage>(&(sdlutils().images().at("asteroid_gold")), 5, 6, 0, 0, 50.0f);

		}
		else 
		{
			a_->addComponent<FramedImage>(&(sdlutils().images().at("asteroid")), 5, 6, 0, 0, 50.0f);
			b_->addComponent<FramedImage>(&(sdlutils().images().at("asteroid")), 5, 6, 0, 0, 50.0f);
		}

		// Como se crean 2 asteroides en vez de disminuir el numero en 1 y sumarlo en 2 al total añadimos solo 1
		numAsteroids++;
	}

	else {
		// Si no le quedan generaciones destruye el asteroide
		numAsteroids--;
	}
	// El asteroide padre se desactiva siempre, se creen hijos o no
	a->setActive(false);

}

void AsteroidsManager::createAsteroid()
{
	int rnd = sdlutils().rand().nextInt(1, 3);
	int gen = sdlutils().rand().nextInt(1, 4);
	
	Vector2D c = Vector2D(sdlutils().width() / 2, sdlutils().height() / 2); //center
	Vector2D f = Vector2D(c.getX() + sdlutils().rand().nextInt(-100,100), c.getY() + sdlutils().rand().nextInt(-100, 100)); //final pos
	Vector2D p = Vector2D(); //pos
	
	int pRnd;
	int r = sdlutils().rand().nextInt(0, 2);
	if (r == 0) {
		r = sdlutils().rand().nextInt(0, 2);
		pRnd = sdlutils().rand().nextInt(0, sdlutils().width() + 1);
		p.setX(pRnd);
		r == 0 ? p.setY(0) : p.setY(sdlutils().height());

	}
	else {
		r = sdlutils().rand().nextInt(0, 2);

		r = sdlutils().rand().nextInt(0, 2);
		pRnd = sdlutils().rand().nextInt(0, sdlutils().width() + 1);
		p.setY(pRnd);
		r == 0 ? p.setX(0) : p.setX(sdlutils().width());
	}
	
	Vector2D v = Vector2D(f - p).normalize() * (sdlutils().rand().nextInt(1, 10) / 10.0f);


	Entity* ast = entity_->getMngr()->addEntity();
	ast->addComponent<Transform>(p, v, 10 + gen * 5, 10 + gen * 5, sdlutils().rand().nextInt(0, 360));
	ast->addComponent<ShowAtOppositeSide>();
	ast->addComponent<Generations>(gen);
	ast->setGroup<Asteroids>(true);

	if (rnd == 1) {
		ast->addComponent<FramedImage>(&(sdlutils().images().at("asteroid")),5,6,0,0,50.0f);
	}
	else {
		ast->addComponent<FramedImage>(&(sdlutils().images().at("asteroid_gold")), 5, 6, 0, 0, 50.0f);
		ast->addComponent<Follow>();
	}

	numAsteroids++;
}
