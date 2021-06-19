#pragma once
#include "../ecs/Component.h"
#include"../utils/Collisions.h"
#include "Transform.h"
#include "AsteroidsManager.h"
#include "State.h"

class CollisionManager :	public Component{

public:
	
	CollisionManager();
	virtual ~CollisionManager();

	virtual void init() override;
	virtual void update() override;


private:

	void onFighterCollision();
	bool collides(Transform* a, Transform* b);

	AsteroidsManager* astManager;
	State* mState;


};

