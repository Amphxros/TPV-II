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
	for (int i = 0; i < n; i++) {
		createAsteroid();
		std::cout << "ast" << std::endl;
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
}
