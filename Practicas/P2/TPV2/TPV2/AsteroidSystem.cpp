#include "AsteroidSystem.h"
#include "ecs/Manager.h"
#include "ShowAtOppositeSide.h"
AsteroidSystem::AsteroidSystem()
{
}

AsteroidSystem::~AsteroidSystem()
{
}

void AsteroidSystem::addAsteroids(int n)
{
	for(int i=0; i<n;i++){
		//Entity* e= manager_->addEntity();
		//e->setGroup<Asteroid>(true);
		//e->addComponent<Transform>(Vector2D(), Vector2D(), 50, 50, 0);
		//e->addComponent<Image>();
		//e->addComponent<ShowAtOppositeSide>();
		//cmps aqui
	}
}

void AsteroidSystem::onCollisionWithBullet(Entity* a, Entity* b)
{

}

void AsteroidSystem::update()
{
}

void AsteroidSystem::receive(const Message& m)
{

}
