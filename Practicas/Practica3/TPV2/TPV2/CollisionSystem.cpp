// This file is part of the course TPV2@UCM - Samir Genaim

#include "CollisionSystem.h"
#include "GameManagerSystem.h"

#include <cassert>
#include "components/Transform.h"
#include "ecs/Manager.h"
#include "sdlutils/SDLUtils.h"
#include "utils/Collisions.h"
#include "GameManagerSystem.h"
#include "NetworkSystem.h"
#include "ecs/Manager.h"

CollisionSystem::CollisionSystem() :
		fighterA(nullptr), //
		fighterB(nullptr), //
		Explosion(nullptr) {

}

CollisionSystem::~CollisionSystem() {
}

void CollisionSystem::init() {
	fighterA = manager_->getHandler<FighterA>();
	fighterB = manager_->getHandler<FighterB>();
}

void CollisionSystem::update() {

	auto entities = manager_->getEnteties();

	for(auto b:entities){
		if(manager_->hasGroup<Bullet>(b)){
	
			auto trA = manager_->getComponent<Transform>(fighterA);
			auto trB = manager_->getComponent<Transform>(fighterB);
			auto trBullet = manager_->getComponent<Transform>(b);

			if(isOnCollision(trA,trBullet)){
				manager_->getSystem<GameManagerSystem>()->onCollisionWithBullet(0);
				manager_->setActive(b, false);
				sdlutils().soundEffects().at("explosion").play();
			}
			else if(isOnCollision(trB,trBullet)){
				manager_->getSystem<GameManagerSystem>()->onCollisionWithBullet(1);
				manager_->setActive(b, false);
				sdlutils().soundEffects().at("explosion").play();		
			}

		}
	}
}


bool CollisionSystem::isOnCollision(Transform* tA, Transform* tB)
{
	return (Collisions::collidesWithRotation(tA->pos_, tA->width_, tA->height_, tA->rotation_, tB->pos_, tB->width_, tB->height_, tB->rotation_));
}
