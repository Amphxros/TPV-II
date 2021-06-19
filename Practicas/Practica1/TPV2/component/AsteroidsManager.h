#pragma once
#include "../ecs/Component.h"

class State;
class AsteroidsManager :
		public Component{

public:

	AsteroidsManager();
	AsteroidsManager(double astPerTime, int initialAsteroids);
	virtual ~AsteroidsManager();

	virtual void init() override;
	virtual void update() override;
	void onCollisionWithBullet(Entity* a);

	void initGame();
	void endGame();

	bool noMoreAsteroids() { return numAsteroids == 0; }

private:
	void createAsteroid();
	double time_;
	double lastCreatedTime_; 
	double asteroidperTime;
	int numAsteroids;	//current number of asteroids
	int initAsteroids; //initial number of asteroids
	State* mState_;
};

