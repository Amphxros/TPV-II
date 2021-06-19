//#include "Gun.h"
//#include "../ecs/Manager.h"
//#include "../sdlutils/InputHandler.h"
//#include "../sdlutils/SDLUtils.h"
//#include "Image.h"
//#include "DisableOnExit.h"
//#include "State.h"
//
//Gun::Gun(double time): time_(time), tr_(nullptr), lastCreatedTime(0)
//{
//}
//
//Gun::~Gun()
//{
//}
//
//void Gun::init()
//{
//	tr_ = entity_->getComponent<Transform>();
//	lastCreatedTime = sdlutils().currRealTime() - time_;
//	assert(tr_ != nullptr);
//}
//
//void Gun::update()
//{
//
//	if(ih().keyDownEvent() && entity_->getMngr()->getHandler<GM>()->getComponent<State>()->getGameState() == GameState::RUNNING){
//		if (ih().isKeyDown(SDLK_s) && sdlutils().currRealTime() - lastCreatedTime > time_) {
//			lastCreatedTime = sdlutils().currRealTime();
//			Vector2D p = tr_->getPos();
//			Vector2D v = tr_->getDir();
//			int w = tr_->getW();
//			int h = tr_->getH();
//			int r = tr_->getRotation();
//			
//			p = p + Vector2D(w / 2, h / 2) - Vector2D(0.0f, h / 2.0f + 5.0f + 12.0f).rotate(r) - Vector2D(2.0f, 10.0f);
//			v = Vector2D(0.0f, -1.0f).rotate(r) * (v.magnitude() + 5.0f);
//
//			Entity* e = entity_->getMngr()->addEntity();
//			e->addComponent<Transform>(p, v, 10, 10, r);
//			e->addComponent<Image>(&sdlutils().images().at("fire"));
//			e->addComponent<DisableOnExit>();
//
//			e->setGroup<Bullets>(true);
//
//			sdlutils().soundEffects().at("fire").play(0,1);
//
//
//		}
//	}
//}
