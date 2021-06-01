#include "FighterSystem.h"

#include "components/Transform.h"
#include "FighterCtrl.h"
#include "BulletsSystem.h"
#include "GameManagerSystem.h"
#include "components/Image.h"

#include "ecs/Manager.h"
#include "sdlutils/InputHandler.h"
#include "sdlutils/SDLUtils.h"
#include "NetworkSystem.h"
#include "ecs/ecs_defs.h"

FighterSystem::FighterSystem():System(), fighterA(nullptr), fighterB(nullptr)
{
}

void FighterSystem::init()
{
	//create fighterA
	fighterA = manager_->addEntity();
	Texture* tA = &(sdlutils().images().at("fighterA"));
	manager_->addComponent<Transform>(fighterA, Vector2D(50, sdlutils().height() / 2.0 - 25), Vector2D(), 50, 50, 90.0f);
	manager_->addComponent<FighterCtrl>(fighterA,SDL_SCANCODE_UP, SDL_SCANCODE_DOWN,SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, 5.0f);
	manager_->addComponent<Image>(fighterA, tA); //modificar el json
	
	//create FighterB
	fighterB = manager_->addEntity();
	
	Texture* tB = &(sdlutils().images().at("fighterB"));
	manager_->addComponent<Transform>(fighterB, Vector2D(sdlutils().width()-50, sdlutils().height() / 2.0 - 25), Vector2D(), 50, 50, -90.0f);
	manager_->addComponent<FighterCtrl>(fighterB, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, 5.0f);
	manager_->addComponent<Image>(fighterB, tB ); //modificar el json

	//handlers of the fighters
	manager_->setHandler<FighterA>(fighterA);
	manager_->setHandler<FighterB>(fighterB);

}

void FighterSystem::update()
{
	if (manager_->getSystem<GameManagerSystem>()->getState() == GameManagerSystem::RUNNING) {
		Uint8 mID = manager_->getSystem<NetworkSystem>()->getId();

		if (mID == 0) {
			moveFighter(fighterA);
		}
		else {
			moveFighter(fighterB);
		}
	}
}

void FighterSystem::resetFighters()
{
	manager_->getComponent<Transform>(fighterA)->pos_=Vector2D(50, sdlutils().height() / 2.0 - 25);
	manager_->getComponent<Transform>(fighterB)->pos_ = Vector2D(sdlutils().width() - 50, sdlutils().height() / 2.0 - 25);
}

void FighterSystem::setFighterPosition(Uint8 id, Vector2D pos, float rotation)
{
	if (id == 0) {
		auto trA = manager_->getComponent<Transform>(fighterB);
		trA->pos_ = pos;
		trA->rotation_ = rotation;
	}
	else {

		auto trB = manager_->getComponent<Transform>(fighterA);
		trB->pos_ = pos;
		trB->rotation_ = rotation;
	}
}

void FighterSystem::moveFighter(Entity* e)
{
	auto tr_ = manager_->getComponent<Transform>(e);
	auto ctrl = manager_->getComponent<FighterCtrl>(e);

	if (ih().keyDownEvent()) {
		if (ih().isKeyDown(ctrl->up_)) {
			tr_->vel_ = tr_->vel_ + Vector2D(0, -1).rotate(tr_->rotation_) * 0.25;
		}
		else if (ih().isKeyDown(ctrl->down_)) {
			tr_->vel_ = tr_->vel_ + Vector2D(0, 1).rotate(tr_->rotation_) * 0.25;
		}
		else if (ih().isKeyDown(ctrl->right_)) {
			tr_->rotation_+=5;
		}
		else if (ih().isKeyDown(ctrl->left_)) {
			tr_->rotation_ -= 5;
		}
		else {
			tr_->vel_.set(new Vector2D());
		}

		if (ih().isKeyDown(SDLK_s)) {
	
			Vector2D p;
			Vector2D v;
			
			p = tr_->pos_ + Vector2D(tr_->width_ / 2.0f, tr_->height_ / 2.0f) - Vector2D(0.0f, tr_->height_ / 2.0f + 5.0f + 12.0f).rotate(tr_->rotation_) - Vector2D(2.0f, 10.0f);
			v = Vector2D(0.0f, -1.0f).rotate(tr_->rotation_) * (tr_->vel_.magnitude() + 5.0f);

			manager_->getSystem<BulletsSystem>()->shoot(p,v,10,10);
			manager_->getSystem<NetworkSystem>()->sendBulletInfo(p,v, 10,10);
		}
	}
	tr_->pos_ = tr_->pos_ + tr_->vel_;
	
	//show at oppositeside component
	if (tr_->pos_.getY() < 0) {
		tr_->pos_.setY(sdlutils().height()-tr_->height_);
	}
	else if (tr_->pos_.getY() + tr_->height_ > sdlutils().height()) {
		tr_->pos_.setY(tr_->height_);
	}
	if (tr_->pos_.getX() < 0) {
		tr_->pos_.setX(sdlutils().width() - tr_->width_);
	}
	else if (tr_->pos_.getX() + tr_->width_ > sdlutils().width()) {

		tr_->pos_.setX(0);
	}
	

	// setea la posicion al otro jugador
	manager_->getSystem<NetworkSystem>()->sendFighterPosition(tr_->pos_,tr_->rotation_);

}
