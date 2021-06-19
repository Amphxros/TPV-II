#pragma once
#include "ecs/Component.h"
#include"utils/Collisions.h"
#include "Transform.h"
#include "AsteroidsManager.h"
#include "State.h"

class CollisionManager :	public Component{

public:
	
	CollisionManager();
	virtual ~CollisionManager();

	virtual void init() override;
	virtual void update() override;

	void onFighterCollision();

private:

	bool collides(Transform* a, Transform* b);

	AsteroidsManager* astManager;
	State* mState;


};

