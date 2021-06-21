#include "FighterSystem.h"


#include "sdlutils/SDLUtils.h"
#include "sdlutils/InputHandler.h"

#include "ecs/Manager.h"
#include "component/Transform.h"
#include "component/Image.h"
#include "component/Health.h"
#include "component/ShowAtOppositeSide.h"
#include "component/DeAcceleration.h"


FighterSystem::FighterSystem() : System()
{
}

FighterSystem::~FighterSystem()
{
}

void FighterSystem::init()
{
	Entity* e = manager_->addEntity();
	manager_->setHandler<Fighter>(e);

	Transform* tr= manager_->addComponent<Transform>(e, Vector2D(sdlutils().width()/2 -25, sdlutils().height()/2- 25),Vector2D(), 50,50,0);
	manager_->addComponent<DeAcceleration>(e, 0.995);
	manager_->addComponent<Image>(e, &sdlutils().images().at("fighter"));
	manager_->addComponent<Health>(e, 3, &sdlutils().images().at("heart"));
	manager_->addComponent<ShowAtOppositeSide>(e, tr);

}

void FighterSystem::update()
{
	if (active) {
		Entity* e = manager_->getHandler<Fighter>();
		Transform* tr_ = manager_->getComponent<Transform>(e);

		ShowAtOppositeSide* s = manager_->getComponent<ShowAtOppositeSide>(e);
		DeAcceleration* d = manager_->getComponent<DeAcceleration>(e);
		if (ih().keyDownEvent()) {
			if (ih().isKeyDown(SDL_SCANCODE_UP)) {
				auto dir = tr_->getDir();
				dir = dir + Vector2D(0, -1).rotate(tr_->getRotation()) * 0.2f;
				
				sdlutils().soundEffects().at("thrust").play();
				tr_->setDir(dir);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_LEFT)) {

				tr_->setRotation(tr_->getRotation() - 5);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_RIGHT)) {
				tr_->setRotation(tr_->getRotation() + 5);
			}
		}
		tr_->setPos(tr_->getPos() + tr_->getDir() * d->getThrust());

		s->update();
	}

}

void FighterSystem::receive(const msg::Message& m)
{
	Health* h = manager_->getComponent<Health>(manager_->getHandler<Fighter>());
	switch (m.id)
	{
	case msg::START_GAME:
		sdlutils().musics().at("imperial_march").play();
		active = true;
		break;
	case msg::COLLISIONFIGHTER:
		active = false;
		onAsteroidCollision();
		break;
	case msg::INIT_GAME:
	
		h->resetHealth();
		break;
	default:
		break;
	}
}

void FighterSystem::onAsteroidCollision()
{
	msg::Message msg_;

	//reseteamos la posicion
	Transform* tr_ = manager_->getComponent<Transform>(manager_->getHandler<Fighter>());
	tr_->setPos(sdlutils().width() / 2 - 25, sdlutils().height() / 2 - 25);
	tr_->setDir(Vector2D());
	tr_->setRotation(0);

	//quitamos vida
	Health* h = manager_->getComponent<Health>(manager_->getHandler<Fighter>());
	int curr = h->getHealth();
	curr--;
	h->setHealth(curr);

	//si aun queda vida o no mandamos el mensaje correspondiente
	if (curr <= 0) {
		msg_.id = msg::GAMEOVER;
		
		msg_.info.currState = 3;
		msg_.info.hasWon = false;
	}
	else {
		msg_.id = msg::ROUNDOVER;
		msg_.info.currState = 2;
	}
	sdlutils().musics().at("imperial_march").haltMusic();
	manager_->send(msg_);
	
	//sdlutils().soundEffects().at("explosion").play();
}