#pragma once
#include "ecs/System.h"
#include <cstddef>
#include "Message.h"
class Entity;
class AsteroidSystem :
	public System
{
public:
	AsteroidSystem();
	virtual ~AsteroidSystem();

	virtual void init() override;
	virtual void update() override;
	void receive(const msg::Message& m) override;
private:
	void addAsteroids(int n);
	void createAsteroid();
	void onCollisionWithBullet(Entity* a, Entity* b);
	std::size_t numOfAsteroids_;

};

