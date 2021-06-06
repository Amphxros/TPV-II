#include "RenderSystem.h"

#include "../components/Image.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"

RenderSystem::RenderSystem() :
	isRunning_(false), //
	isGameOver_(false), //
	isNewGame_(false), //
	fighterWon_(false), //
	remainingRounds_(0), //
	fighter_(nullptr), //
	bullet_(nullptr), //
	loserMsg_(nullptr), //
	asteroid_(nullptr), //
	asteroidGold_(nullptr){
}

RenderSystem::~RenderSystem()
{
}

void RenderSystem::init() {
	fighter_ = &sdlutils().images().at("fighter");
	bullet_ = &sdlutils().msgs().at("bullet");
	asteroid_ = &sdlutils().msgs().at("asteroid");
	asteroidGold_ = &sdlutils().msgs().at("asteroid_gold");
}

void RenderSystem::update()
{
	// Orden de renderizado para sobreponer la interfaz
	drawEntitiesWithImage();
	drawRounds();
	drawMsgs();
}

void RenderSystem::receive(const Message &m)
{
	switch (m.type_) {
	case _ROUND_START_:
		isRunning_ = true;
		isNewGame_ = false;
		remainingRounds_ = msg.round_.remainingRounds_;
		break;
	case _ROUND_OVER_:
		isRunning_ = false;
		remainingRounds_ = msg.round_.remainingRounds_;
		break;
	case _GAME_START_:
		isGameOver_ = false;
		isNewGame_ = true;
		fighterWon_ = msg.round_.fighterWon_;
		remainingRounds_ = msg.round_.remainingRounds_;
		break;
	case _GAME_OVER_:
		isGameOver_ = true;
		fighterWon_ = msg.round_.fighterWon_;
		remainingRounds_ = msg.round_.remainingRounds_;
		break;
	default:
		break;
	}
}

void RenderSystem::drawMsgs()
{

	if (!isRunning_) {

	}

}

void RenderSystem::drawLives()
{
	SDL_Rect dest{ 0, 5, 25, 25 };
	for (int i = 0; i < remainingRounds_; i++) {
		dest.x = i * 26;
		roundImg_->render(dest);
	}
}

void RenderSystem::drawEntitiesWithImage()
{
	// Renderiza ambos tipos de Asteroide
	for (auto e : mngr->getEntities()) {
		if (e->hasGroup(ecs::AsteroidsGroup)) {
			e->render();
		}
	}
	// Renderiza todas las balas activas
	for (auto e : mngr->getEntities()) {
		if (e->hasGroup(ecs::BulletsGroup)) {
			e->render();
		}
	}
	// Renderiza el Fighter
	mngr->getHandler(ecs::FighterHndlr)->render();
}
