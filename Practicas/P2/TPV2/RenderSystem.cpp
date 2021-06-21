#include "RenderSystem.h"
#include "ecs/Manager.h"

#include "component/Transform.h"
#include "component/Image.h"
#include "component/FramedImage.h"
#include "component/Health.h"
#include "sdlutils/SDLUtils.h"

RenderSystem::RenderSystem() : 
	System(),currState(0), initMsg(nullptr), pauseMsg(nullptr), gameOverMsg(nullptr), gameWinMsg(nullptr)
{
}

RenderSystem::~RenderSystem()
{
}

void RenderSystem::init()
{
	initMsg = &sdlutils().msgs().at("init");
	pauseMsg = &sdlutils().msgs().at("pause");
	gameOverMsg = &sdlutils().msgs().at("gameOver");
	gameWinMsg = &sdlutils().msgs().at("gameWin");
}

void RenderSystem::update()
{
	renderAsteroids();
	renderBullets();
	renderFighter();
	renderRemainingLives();
	renderMsgs();
}

void RenderSystem::receive(const msg::Message& m)
{
	switch (m.id)
	{
	case msg::ROUNDOVER: //pasado a paused
		currState = m.info.currState;
		break;
	case msg::START_GAME: //pasado a running
		currState = m.info.currState;
		break;
	case msg::GAMEOVER:	//pasado a estado GameOver
		if (m.info.hasWon) {
			currState = 4; //el 4 es porque no existe ningun estado gameWin
		}
		else {
			currState = m.info.currState; 
		}
		break;
	case msg::INIT_GAME: //pasado a estado new
		currState = m.info.currState;
		break;
	default:
		break;
	}
}

void RenderSystem::renderAsteroids()
{
	//renderiza todos los asteroides y actualiza su animacion
	for (Entity* ent : manager_->getEnteties()) {
		if (manager_->hasGroup<Asteroids>(ent)) {
			auto tr = manager_->getComponent<Transform>(ent);
			auto im = manager_->getComponent<FramedImage>(ent);
			im->update();
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
	//renderiza todas las balas
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
	//renderiza el fighter
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
	//renderiza la vida restante del jugaador
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

void RenderSystem::renderMsgs()
{
	SDL_Rect dest;
	switch (currState)
	{
	case 0:		//state new
		dest.x = (int)(sdlutils().width() / 2 - initMsg->width()) / 2;
		dest.y = (int)(sdlutils().height()- initMsg->height()) / 2 - 100;
		dest.w = (int)sdlutils().width() / 2;
		dest.h = (int)sdlutils().height() / 3;
		initMsg->render(dest);
	
		break;
	case 2:		//state pause

		dest.x = (int)(sdlutils().width() / 2 - pauseMsg->width()) / 2;
		dest.y = (int)(sdlutils().height() - pauseMsg->height()) / 2 - 100;
		dest.w = (int)sdlutils().width() / 2;
		dest.h = (int)sdlutils().height() / 3;
		pauseMsg->render(dest);

		break;

	case 3:		//state game over
		dest.x = (int)(sdlutils().width() / 2 - gameOverMsg->width()) / 2;
		dest.y = (int)(sdlutils().height() - gameOverMsg->height()) / 2 - 100;
		dest.w = (int)sdlutils().width() / 2;
		dest.h = (int)sdlutils().height() / 3;
		gameOverMsg->render(dest);
		break;
	case 4:		//state game over pero no hay mas asteroides
		dest.x = (int)(sdlutils().width() - gameWinMsg->width()) / 2;
		dest.y = (int)(sdlutils().height() - gameWinMsg->height()) / 2 - 100;
		dest.w = (int)sdlutils().width() / 2;
		dest.h = (int)sdlutils().height() / 3;
		gameWinMsg->render(dest);
		break;
	default:
		break;
	}
}
