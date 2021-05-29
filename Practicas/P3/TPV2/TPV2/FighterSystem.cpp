#include "FighterSystem.h"

#include "components/Transform.h"
#include "ecs/Manager.h"
#include "sdlutils/InputHandler.h"
#include "sdlutils/SDLUtils.h"
#include "FighterCtrl.h"
#include "NetworkSystem.h"
#include "ecs_defs.h"
FighterSystem::FighterSystem()
{
}

void FighterSystem::init()
{
	//create fighterA
	fighterA = manager_->addEntity();
	manager_->addComponent<Transform>(fighterA, Vector2D(50, sdlutils().height() / 2.0 - 25), Vector2D(), 50, 50, 90.0f);
	manager_->addComponent<FighterCtrl>(fighterA,SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_SPACE, 5.0f);
	manager_->addComponent<Image>(fighterA); //modificar el json
	
	//create FighterB
	fighterB = manager_->addEntity();
	manager_->addComponent<Transform>(fighterB, Vector2D(sdlutils().width()-50, sdlutils().height() / 2.0 - 25), Vector2D(), 50, 50, 90.0f);
	manager_->addComponent<FighterCtrl>(fighterB, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_SPACE, 5.0f);
	manager_->addComponent<Image>(fighterB); //modificar el json

	//handlers of the fighters
	manager_->setHandler<FighterA>(fighterA);
	manager_->setHandler<FighterB>(fighterB);

}

void FighterSystem::update()
{
	Uint8 mID = manager_->getSystem<NetworkSystem>()->getId();

	if (mID == 0) {
		moveFighter(fighterA);
	}
	else {
		moveFighter(fighterB);
	}

}

void FighterSystem::setFighterPosition(Uint8 id, Vector2D pos)
{
	if (id == 0) {
		auto trA = manager_->getComponent<Transform>(fighterA);
		trA->pos_ = pos;
	}
	else {

		auto trB = manager_->getComponent<Transform>(fighterB);
		trB->pos_ = pos;
	}
}

void FighterSystem::moveFighter(Entity* e)
{
	auto tr_ = manager_->getComponent<Transform>(e);
	auto ctrl = manager_->getComponent<FighterCtrl>(e);

	if (ih().keyDownEvent()) {
		if (ih().isKeyDown(ctrl->up_)) {
			tr_->vel_.setY(-ctrl->speed_);
		}
		else if (ih().isKeyDown(ctrl->down_)) {
			tr_->vel_.setY(ctrl->speed_);
		}
		else if (ih().isKeyDown(ctrl->right_)) {
			tr_->vel_.setX(ctrl->speed_);
		}
		else if (ih().isKeyDown(ctrl->left_)) {
			tr_->vel_.setX(-ctrl->speed_);
		}
		else {
			tr_->vel_.set(new Vector2D());
		}
	}
	tr_->pos_ = tr_->pos_ + tr_->vel_;
	
	//show at oppositeside component
	if (tr_->pos_.getY() < 0) {
		tr_->pos_.setY(sdlutils().height);
	}
	else if (tr_->pos_.getY() + tr_->height_ > sdlutils().height()) {

		tr_->pos_.setY(0);
	}
	if (tr_->pos_.getX() < 0) {
		tr_->pos_.setX(sdlutils().width());
	}
	else if (tr_->pos_.getX() + tr_->width_ > sdlutils().width()) {

		tr_->pos_.setX(0);
	}

	manager_->getSystem<NetworkSystem>()->sendFighterPosition(tr_->pos_);

}
