//#include "FighterCtrl.h"
//#include "ecs/Manager.h"
//#include "sdlutils/InputHandler.h"
//#include "sdlutils/SDLUtils.h"
//#include "State.h"
//
//FighterCtrl::FighterCtrl(float speed, float thrust, float maxSpeed): 
//	Component(), speed_(speed), thrust_(thrust), maxSpeed_(maxSpeed)
//{
//}
//
//FighterCtrl::~FighterCtrl()
//{
//}
//
//void FighterCtrl::init()
//{
//	tr_ = entity_->getComponent<Transform>();
//	assert(tr_ != nullptr);
//}
//
//void FighterCtrl::update()
//{
//	if (entity_->getMngr()->getHandler<GM>()->getComponent<State>()->getGameState() == GameState::RUNNING) {
//		auto dir = tr_->getDir();
//
//		if (ih().keyDownEvent()) {
//			if (ih().isKeyDown(SDL_SCANCODE_UP)) {
//				dir = dir + Vector2D(0, -1).rotate(tr_->getRotation()) * thrust_;
//				sdlutils().soundEffects().at("thrust").play();
//			}
//
//			else if (ih().isKeyDown(SDL_SCANCODE_LEFT)) {
//
//				tr_->setRotation(tr_->getRotation() - 5);
//			}
//			else if (ih().isKeyDown(SDL_SCANCODE_RIGHT)) {
//
//				tr_->setRotation(tr_->getRotation() + 5);
//			}
//		}
//
//		if (dir.magnitude() >= maxSpeed_) {
//			dir = dir.normalize() * maxSpeed_;
//		}
//
//		tr_->setDir(dir);
//	}
//}
