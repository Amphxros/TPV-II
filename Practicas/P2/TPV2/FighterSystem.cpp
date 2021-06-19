#include "FighterSystem.h"
#include "ecs/Manager.h"

#include "sdlutils/SDLUtils.h"
#include "sdlutils/InputHandler.h"

#include "component/Transform.h"
#include "component/Health.h"
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

	manager_->addComponent<Transform>(e, Vector2D(sdlutils().width()/2 -25, sdlutils().height()/2- 25),Vector2D(), 50,50,0);
	manager_->addComponent<Image>(e, &sdlutils().images().at("fighter"));
	manager_->addComponent<Health>(e,3, &sdlutils().images().at("heart"));
	

}

void FighterSystem::update()
{
	if (!active) {
		return;
	}
	else {
		Transform* tr_ = manager_->getComponent<Transform>(manager_->getHandler<Fighter>());

		if (ih().keyDownEvent()) {
			if (ih().isKeyDown(SDL_SCANCODE_UP)) {
				auto dir = tr_->getDir();
				dir = dir + Vector2D(0, -1).rotate(tr_->getRotation()) * 0.2f;
				sdlutils().soundEffects().at("thrust").play();
			}
			else if (ih().isKeyDown(SDL_SCANCODE_LEFT)) {

				tr_->setRotation(tr_->getRotation() - 5);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_RIGHT)) {
				tr_->setRotation(tr_->getRotation() + 5);
			}
		}

	}
}

void FighterSystem::receive(const msg::Message& m)
{
	switch (m.id)
	{
	case msg::START_GAME:
		active = true;
		break;
	case msg::COLLISIONFIGHTER:
		active = false;
		onAsteroidCollision();
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
	tr_->setRotation(0);

	//quitamos vida
	Health* h = manager_->getComponent<Health>(manager_->getHandler<Fighter>());
	int curr = h->getHealth();
	curr--;
	h->setHealth(curr);

	//si aun queda vida o no mandamos el mensaje correspondiente
	if (curr <= 0) {
		msg_.id = msg::GAMEOVER;
	}
	else {
		msg_.id = msg::ROUNDOVER;
	}
	manager_->send(msg_);
}
