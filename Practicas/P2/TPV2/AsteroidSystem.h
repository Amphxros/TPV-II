#pragma once
#include <cstddef>

#include "ecs/System.h"
#include "Message.h"

class Entity;
class AsteroidSystem :	public System{

public:

	AsteroidSystem(double time);
	virtual ~AsteroidSystem();

	virtual void init() override;
	virtual void update() override;
	void receive(const msg::Message& m) override;

private:

	void addAsteroids(int n);
	void createAsteroid();
	void onCollisionWithBullet(Entity* a, Entity* b);

	std::size_t numOfAsteroids_;
	bool active;
	// Tiempo para generar nuevos asteroides
	double timeSinceLastAsteroid_;
	double currTime_;

};

