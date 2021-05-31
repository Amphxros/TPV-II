// This file is part of the course TPV2@UCM - Samir Genaim

#include "CollisionSystem.h"

#include <cassert>
#include "components/Transform.h"
#include "ecs/Manager.h"
#include "sdlutils/SDLUtils.h"
#include "utils/Collisions.h"
#include "BallSystem.h"
#include "GameManagerSystem.h"
#include "NetworkSystem.h"

CollisionSystem::CollisionSystem() :
		ballTr_(nullptr), //
		leftPaddelTr_(nullptr), //
		rightPaddelTr_(nullptr), //
		paddleHit_(nullptr) {

}

CollisionSystem::~CollisionSystem() {
}

void CollisionSystem::init()
{
}

//void CollisionSystem::init() {
//	paddleHit_ = &sdlutils().soundEffects().at("paddle_hit");
//	ballTr_ = manager_->getComponent<Transform>(manager_->getHandler<Ball>());
//	assert(ballTr_ != nullptr);
//	leftPaddelTr_ = manager_->getComponent<Transform>(
//			manager_->getHandler<LeftPaddle>());
//	assert(leftPaddelTr_ != nullptr);
//	rightPaddelTr_ = manager_->getComponent<Transform>(
//			manager_->getHandler<RightPaddle>());
//	assert(rightPaddelTr_ != nullptr);
//}

void CollisionSystem::update() {


}
