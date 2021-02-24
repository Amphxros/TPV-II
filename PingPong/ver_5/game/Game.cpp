// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "Container.h"
#include "PingPongFactory.h"

Game::Game() {
}

Game::~Game() {
	// delete all game objects
	for (GameObject *o : objs_) {
		delete o;
	}
}

void Game::init(PingPongFactory &factory) {

	// initialize the SDL singleton
	SDLUtils::init("Ping Pong", 800, 600,
			"resources/config/pingpong.resources.json");

	// the ball
	GameObject *ball = factory.createBall();
	GameObject *leftPaddle = factory.createLeftPaddle(ball);
	GameObject *rightPaddle = factory.createRightPaddle(ball);
	GameObject *gm = factory.createGameManager(ball, leftPaddle, rightPaddle);

	// add them all to the list of game objects
	objs_.push_back(ball);
	objs_.push_back(leftPaddle);
	objs_.push_back(rightPaddle);
	objs_.push_back(gm);

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

		for (auto &o : objs_) {
			o->handleInput();
		}

		// update
		for (auto &o : objs_) {
			o->update();
		}

		sdlutils().clearRenderer();

		// render
		for (auto &o : objs_) {
			o->render();
		}

		sdlutils().presentRenderer();
		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
	}

}

