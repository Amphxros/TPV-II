#include "AsteroidSystem.h"

#include "sdlutils/SDLUtils.h"
#include "ecs/Manager.h"
#include "ecs/ecs_defs.h"

AsteroidSystem::AsteroidSystem(): System(), numOfAsteroids_(0)
{
}

AsteroidSystem::~AsteroidSystem()
{
}

void AsteroidSystem::init()
{
}

void AsteroidSystem::update()
{
	for (auto& ent : manager_->getEnteties()) {
		if (manager_->hasGroup<Asteroids>(ent)) {
			Transform* tr_ = manager_->getComponent<Transform>(ent);
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
		addAsteroids(m.num.n);
		break;
	case msg::ROUNDOVER:
	case msg::GAMEOVER:
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
	}
}

void AsteroidSystem::createAsteroid()
{
	//int rnd = sdlutils().rand().nextInt(1, 3);
	//	int gen = sdlutils().rand().nextInt(1, 4);
	//	
	//	Vector2D c = Vector2D(sdlutils().width() / 2, sdlutils().height() / 2); //center
	//	Vector2D f = Vector2D(c.getX() + sdlutils().rand().nextInt(-100,100), c.getY() + sdlutils().rand().nextInt(-100, 100)); //final pos
	//	Vector2D p = Vector2D(); //pos
	//	
	//	int pRnd;
	//	int r = sdlutils().rand().nextInt(0, 2);
	//	if (r == 0) {
	//		r = sdlutils().rand().nextInt(0, 2);
	//		pRnd = sdlutils().rand().nextInt(0, sdlutils().width() + 1);
	//		p.setX(pRnd);
	//		r == 0 ? p.setY(0) : p.setY(sdlutils().height());
	//
	//	}
	//	else {
	//		r = sdlutils().rand().nextInt(0, 2);
	//
	//		r = sdlutils().rand().nextInt(0, 2);
	//		pRnd = sdlutils().rand().nextInt(0, sdlutils().width() + 1);
	//		p.setY(pRnd);
	//		r == 0 ? p.setX(0) : p.setX(sdlutils().width());
	//	}
	//	
	//	Vector2D v = Vector2D(f - p).normalize() * (sdlutils().rand().nextInt(1, 10) / 10.0f);
	//
	//
	//	Entity* ast = entity_->getMngr()->addEntity();
	//	ast->addComponent<Transform>(p, v, 10 + gen * 5, 10 + gen * 5, sdlutils().rand().nextInt(0, 360));
	//	ast->addComponent<ShowAtOppositeSide>();
	//	ast->addComponent<Generations>(gen);
	//	ast->setGroup<Asteroids>(true);
	//
	//	if (rnd == 1) {
	//		ast->addComponent<FramedImage>(&(sdlutils().images().at("asteroid")),5,6,0,0,50.0f);
	//	}
	//	else {
	//		ast->addComponent<FramedImage>(&(sdlutils().images().at("asteroid_gold")), 5, 6, 0, 0, 50.0f);
	//		ast->addComponent<Follow>();
	//	}
	//
	//	numAsteroids++;
}

void AsteroidSystem::onCollisionWithBullet(Entity* a, Entity* b)
{
}
