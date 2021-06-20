#include "RenderSystem.h"
#include "ecs/Manager.h"

#include "component/Transform.h"
#include "component/Image.h"
#include "component/FramedImage.h"
#include "component/Health.h"

RenderSystem::RenderSystem()
{
}

RenderSystem::~RenderSystem()
{
}

void RenderSystem::init()
{
}

void RenderSystem::update()
{
	renderAsteroids();
	renderBullets();
	renderFighter();
	renderRemainingLives();
}

void RenderSystem::receive(const msg::Message& m)
{
}

void RenderSystem::renderAsteroids()
{
	for (Entity* ent : manager_->getEnteties()) {
		if (manager_->hasGroup<Asteroids>(ent)) {
			auto tr = manager_->getComponent<Transform>(ent);
			auto im = manager_->getComponent<FramedImage>(ent);
			SDL_Rect dest;
			dest.x = (int)tr->getPos().getX();
			dest.y = (int)tr->getPos().getY();
			dest.w = (int)tr->getW();
			dest.h = (int)tr->getH();

			im->getTexture()->render(im->getSrc(), dest, tr->getRotation());

		}
	}
}

void RenderSystem::renderBullets()
{
	auto entities = manager_->getEnteties();
	for (auto e : entities) {
		if (manager_->hasGroup<Bullets>(e)) {
			auto tr = manager_->getComponent<Transform>(e);
			auto im = manager_->getComponent<Image>(e);

			SDL_Rect dest;
			dest.x = (int)tr->getPos().getX();
			dest.y = (int)tr->getPos().getY();
			dest.w = (int)tr->getW();
			dest.h = (int)tr->getH();

			im->getTexture()->render(dest, tr->getRotation());

		}
	}
}

void RenderSystem::renderFighter()
{
	Entity* e = manager_->getHandler<Fighter>();
	Transform* tr = manager_->getComponent<Transform>(e);
	Image* im = manager_->getComponent<Image>(e);

	SDL_Rect dest;
	dest.x = (int)tr->getPos().getX();
	dest.y = (int)tr->getPos().getY();
	dest.w = (int)tr->getW();
	dest.h = (int)tr->getH();

	im->getTexture()->render(dest, tr->getRotation());


}

void RenderSystem::renderRemainingLives()
{
	Entity* e = manager_->getHandler<Fighter>();
	Health* h = manager_->getComponent<Health>(e);

	for (int i = 0; i < h->getHealth(); i++) {
		SDL_Rect dest;
		dest.x = sdlutils().width()- 30 - 22 * i;
		dest.y = 10;
		dest.w = 20;
		dest.h = 20;

		h->getTexture()->render(dest, 0);
	}

}
