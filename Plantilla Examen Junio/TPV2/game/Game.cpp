// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../components/Image.h"
#include "../components/Transform.h"
#include "../ecs/ecs.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../utils/Vector2D.h"
#include "CollisionSystem.h"
#include "FoodSystem.h"
#include "GameManagerSystem.h"
#include "GhostsSystem.h"
#include "PacManSystem.h"
#include "RenderSystem.h"
#include "SoundSystem.h"

Game::Game() {
	mngr_.reset(new Manager());
	collisionSys_ = nullptr;
	gameMngrSys_ = nullptr;
	pacmanSys_ = nullptr;
	ghostsSys_ = nullptr;
	foodSys_ = nullptr;
	soundSystem_ = nullptr;
	renderSys_ = nullptr;
}

Game::~Game() {
}

void Game::init() {

	SDLUtils::init("Ping Pong", 800, 600,
			"resources/config/pacman.resources.json");

	pacmanSys_ = mngr_->addSystem<PacManSystem>();
	ghostsSys_ = mngr_->addSystem<GhostsSystem>();
	foodSys_ = mngr_->addSystem<FoodSystem>();
	collisionSys_ = mngr_->addSystem<CollisionSystem>();
	gameMngrSys_ = mngr_->addSystem<GameManagerSystem>();
	soundSystem_ = mngr_->addSystem<SoundSystem>();
	renderSys_ = mngr_->addSystem<RenderSystem>();
}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;
	SDL_Event event;

	while (!exit) {
		Uint32 startTime = sdlutils().currRealTime();

		ih().clearState();
		while (SDL_PollEvent(&event))
			ih().update(event);

		if (ih().isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}

		mngr_->refresh();

		pacmanSys_->update();
		ghostsSys_->update();
		collisionSys_->update();
		gameMngrSys_->update();

		mngr_->flushMsgsQueue();

		sdlutils().clearRenderer();
		renderSys_->update();
		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
	}

}

