// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "Ball.h"
#include "BallWithImage.h"
#include "Paddle.h"
#include "GameManager.h"
#include "PaddleNoFill.h"
#include "PaddleWithAI.h"
#include "PaddleWithMouse.h"

Game::Game() {
}

Game::~Game() {
	// delete all game objects
	for (GameObject *o : objs_) {
		delete o;
	}
}

void Game::init() {

	// initialize the SDL singleton
	SDLUtils::init("Ping Pong", 800, 600,
			"resources/config/pingpong.resources.json");

	// the ball
	//Ball *ball = new Ball();
	Ball *ball = new BallWithImage(&sdlutils().images().at("tennis_ball"));
	ball->setWidth(10.0f);
	ball->setHeight(10.0f);
	ball->getPos().set(sdlutils().width() / 2 - 5, sdlutils().height() / 2 - 5);

	// the left paddle
	//Paddle *leftPaddle = new Paddle(build_sdlcolor(0xff0000ff));
	Paddle *leftPaddle = new PaddleNoFill(build_sdlcolor(0xff0000ff));
	//Paddle *leftPaddle = new PaddleWithMouse(build_sdlcolor(0xff0000ff));
	//Paddle *leftPaddle = new PaddleWithAI(build_sdlcolor(0xff0000ff), ball);
	leftPaddle->setWidth(10.0f);
	leftPaddle->setHeight(50.0f);
	leftPaddle->getPos().set(10, sdlutils().height() / 2 - 25);
	leftPaddle->setKeys(SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A);

	// the right paddle
//	Paddle *rightPaddle = new Paddle(build_sdlcolor(0x0000ffff));
//	Paddle *rightPaddle = new PaddleNoFill(build_sdlcolor(0x0000ffff));
//	Paddle *rightPaddle = new PaddleWithMouse(build_sdlcolor(0x0000ffff));
	Paddle *rightPaddle = new PaddleWithAI(build_sdlcolor(0x0000ffff), ball);
	rightPaddle->setWidth(10.0f);
	rightPaddle->setHeight(50.0f);
	rightPaddle->getPos().set(sdlutils().width() - 15,
			sdlutils().height() / 2 - 25);
//	rightPaddle->setKeys(SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT);

	GameManager *gm = new GameManager(ball, leftPaddle, rightPaddle);

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
