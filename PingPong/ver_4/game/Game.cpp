// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "BounceOnBorderPC.h"
#include "Container.h"
#include "CtrlMsgRC.h"
#include "EmptyRectRC.h"
#include "FilledRectRC.h"
#include "GameCtrlIC.h"
#include "GameManager.h"
#include "ImageRC.h"
#include "PaddleAIPhysics.h"
#include "PaddleKBCtrlIC.h"
#include "PaddleMouseCtrlIC.h"
#include "PingPongRulePC.h"
#include "ScoreRC.h"
#include "SimpleMovePC.h"
#include "StopOnBorderPC.h"

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
	Container *ball = new Container();
	//ball->addComponent(new RectRC());
	ball->addComponent(new ImageRC(&sdlutils().images().at("tennis_ball")));
	ball->addComponent(new SimpleMovePC());
	ball->addComponent(new BounceOnBorderPC());
	ball->setWidth(10.0f);
	ball->setHeight(10.0f);
	ball->getPos().set(sdlutils().width() / 2 - 5, sdlutils().height() / 2 - 5);
	

	// left paddle
	Container *leftPaddle = new Container();
	leftPaddle->addComponent(new FilledRectRC(build_sdlcolor(0xff0000ff)));

//	auto kbIC = new PaddleKBCtrlIC();
//	kbIC->setKeys(SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A);
//	leftPaddle->addComponent(kbIC);

	leftPaddle->addComponent(new PaddleMouseCtrlIC());
	leftPaddle->addComponent(new SimpleMovePC());
	leftPaddle->addComponent(new StopOnBorderPC());

	leftPaddle->setWidth(10.0f);
	leftPaddle->setHeight(50.0f);
	leftPaddle->getPos().set(10, sdlutils().height() / 2 - 25);


	// right paddle
	Container *rightPaddle = new Container();
	rightPaddle->addComponent(new EmptyRectRC(build_sdlcolor(0x0000ffff)));
	rightPaddle->addComponent(new PaddleAIPhysics(ball));
	rightPaddle->addComponent(new SimpleMovePC());
	rightPaddle->addComponent(new StopOnBorderPC());

	rightPaddle->setWidth(10.0f);
	rightPaddle->setHeight(50.0f);
	rightPaddle->getPos().set(sdlutils().width() - 15,
			sdlutils().height() / 2 - 25);

	Container *gm = new GameManager(ball, leftPaddle, rightPaddle);
	gm->addComponent(new GameCtrlIC());
	gm->addComponent(new PingPongRulePC());
	gm->addComponent(new ScoreRC());
	gm->addComponent(new CtrlMsgRC());

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

