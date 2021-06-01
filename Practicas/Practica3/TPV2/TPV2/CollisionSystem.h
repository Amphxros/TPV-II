// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "ecs/System.h"

struct Transform;
struct Entity;
class SoundEffect;

class CollisionSystem: public System {
public:
	CollisionSystem();
	virtual ~CollisionSystem();
	void init() override;
	void update() override;
	bool isOnCollision(Transform* tA, Transform* tB);
private:

	Entity* fighterA;
	Entity* fighterB;
	SoundEffect* Explosion;
};

