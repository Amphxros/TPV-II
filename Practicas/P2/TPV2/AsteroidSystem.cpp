#include "AsteroidSystem.h"

#include "sdlutils/SDLUtils.h"
#include "ecs/Manager.h"
#include "ecs/ecs_defs.h"
#include "ecs/Entity.h"
#include "component/Transform.h"
#include "component/ShowAtOppositeSide.h"
#include "component/Follow.h"
#include "component/FramedImage.h"
#include "component/Generations.h"

AsteroidSystem::AsteroidSystem(): System(), numOfAsteroids_(0), active(false)
{
}

AsteroidSystem::~AsteroidSystem()
{
}

void AsteroidSystem::init()
{
	active = false;
}

void AsteroidSystem::update()
{
	if (active) {
		for (Entity* ent : manager_->getEnteties()) {
			if (manager_->hasGroup<Asteroids>(ent)) {
				auto tr = manager_->getComponent<Transform>(ent);
				if (manager_->hasComponent<Follow>(ent)) {
					auto f = manager_->getComponent<Follow>(ent);
					f->update();
				}
				manager_->getComponent<ShowAtOppositeSide>(ent)->update();
				tr->setPos(tr->getPos() + tr->getDir());

			}
		}



	}
}

void AsteroidSystem::receive(const msg::Message& m)
{
	switch (m.id)
	{
	case msg::COLLISIONBULLET:
		onCollisionWithBullet(m.col.a, m.col.b);
		sdlutils().soundEffects().at("gunshot").play();
		break;
	case msg::START_GAME:
		active = true;
		addAsteroids(m.num.n);
		break;
	case msg::ROUNDOVER:
	case msg::GAMEOVER:
		active = false;
		for (auto& ent : manager_->getEnteties()) {
			if (manager_->hasGroup<Asteroids>(ent)) {
				manager_->setActive(ent, false);
			}
		}
		break;
	default:
		break;
	}
}

void AsteroidSystem::addAsteroids(int n)
{
	std::cout << n;
	for (int i = 0; i < n; i++) {
		createAsteroid();
	}
}

void AsteroidSystem::createAsteroid()
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
	//	
	
	Vector2D v = Vector2D(f - p).normalize() * (sdlutils().rand().nextInt(1, 10) / 10.0f);
	
	Entity* ast = manager_->addEntity();
	manager_->setGroup<Asteroids>(ast, true);
	
	Transform* tr=manager_->addComponent<Transform>(ast, p, v, 10 + gen * 5, 10 + gen * 5, sdlutils().rand().nextInt(0, 360));
	manager_->addComponent<Generations>(ast,gen);
	manager_->addComponent<ShowAtOppositeSide>(ast,tr);
	

	if (rnd == 1) {
		manager_->addComponent<FramedImage>(ast,&(sdlutils().images().at("asteroid")),5,6,0,0,50.0f);
	}
	else {
		manager_->addComponent<FramedImage>(ast,&(sdlutils().images().at("asteroid_gold")), 5, 6, 0, 0, 50.0f);
		manager_->addComponent<Follow>(ast,tr, manager_->getComponent<Transform>(manager_->getHandler<Fighter>()));
	}
	
	numOfAsteroids_++;

}

void AsteroidSystem::onCollisionWithBullet(Entity* a, Entity* b)
{	
	// Si el asteroide tiene generaciones se divide y hacemos un ++ al total de asteroides (Se destruye el original pero se crean 2)
	if (manager_->getComponent<Generations>(a)->getGen() > 0) {

		Vector2D p = manager_->getComponent<Transform>(a)->getPos();
		Vector2D v = manager_->getComponent<Transform>(a)->getDir();
		double r = manager_->getComponent<Transform>(a)->getRotation();
		double w = manager_->getComponent<Transform>(a)->getW();

		int gen = manager_->getComponent<Generations>(a)->getGen();

		//se divide en 2 asteroides A y B
		//Asteroide A
		Entity* A = manager_->addEntity();

		Vector2D posA = p + v.rotate(r) * 2 * w;
		Vector2D velA = v.rotate(r) * 1.1f;
		Transform* trA = manager_->addComponent<Transform>(A, posA, velA, 10 + 5 * gen - 1, 10 + 5 * gen - 1, sdlutils().rand().nextInt(0, 360));
		manager_->addComponent<ShowAtOppositeSide>(A, trA);
		manager_->addComponent<Generations>(A, gen - 1);

		Entity* B = manager_->addEntity();
		Vector2D posB = p - v.rotate(r) * 2 * w;
		Vector2D velB = v.rotate(r) * 1.1f;
		Transform* trB = manager_->addComponent<Transform>(B, posB, velB, 10 + 5 * gen - 1, 10 + 5 * gen - 1, sdlutils().rand().nextInt(0, 360));
		manager_->addComponent<ShowAtOppositeSide>(B, trB);
		manager_->addComponent<Generations>(B, gen - 1);


		//si el asteroide es de tipo B sus hijos tambien lo son
		if (manager_->hasComponent<Follow>(a)) {

			Transform* tr = manager_->getComponent<Transform>(manager_->getHandler<Fighter>());

			manager_->addComponent<Follow>(A, trA, tr);
			manager_->addComponent<FramedImage>(A, &(sdlutils().images().at("asteroid_gold")), 5, 6, 0, 0, 50.0f);
			manager_->addComponent<Follow>(B, trB, tr);
			manager_->addComponent<FramedImage>(B, &(sdlutils().images().at("asteroid_gold")), 5, 6, 0, 0, 50.0f);

		}
		else
		{
			manager_->addComponent<FramedImage>(A, &(sdlutils().images().at("asteroid")), 5, 6, 0, 0, 50.0f);
			manager_->addComponent<FramedImage>(B, &(sdlutils().images().at("asteroid")), 5, 6, 0, 0, 50.0f);
		}
		numOfAsteroids_++;
		manager_->setGroup<Asteroids>(A, true);
		manager_->setGroup<Asteroids>(B, true);

	
	}
	else {
		numOfAsteroids_--;
	}
	manager_->setActive(a, false);
}
