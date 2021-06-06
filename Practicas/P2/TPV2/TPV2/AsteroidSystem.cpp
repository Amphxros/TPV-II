#include "AsteroidSystem.h"
#include "ecs/Manager.h"
AsteroidSystem::AsteroidSystem()
{
}

AsteroidSystem::~AsteroidSystem()
{
}

void AsteroidSystem::addAsteroids(int n)
{
	for(int i=0; i<n;i++){
		Entity* e= manager_->addEntity();
		//cmps aqui
		manager_->setGroup<Asteroid>(e, true);
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
