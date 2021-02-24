// This file is part of the course TPV2@UCM - Samir Genaim

#include "DefaultPingPongFacoty.h"

#include "../sdlutils/SDLUtils.h"
#include "BounceOnBorderPC.h"
#include "Container.h"
#include "CtrlMsgRC.h"
#include "EmptyRectRC.h"
#include "FilledRectRC.h"
#include "GameCtrlIC.h"
#include "PaddleAIPhysics.h"
#include "PaddleKBCtrlIC.h"
#include "PingPongRulePC.h"
#include "ScoreRC.h"
#include "SimpleMovePC.h"
#include "StopOnBorderPC.h"

DefaultPingPongFacoty::DefaultPingPongFacoty() {
	// TODO Auto-generated constructor stub

}

DefaultPingPongFacoty::~DefaultPingPongFacoty() {
}

GameObject* DefaultPingPongFacoty::createRightPaddle(GameObject *ball) {

	Container *rightPaddle = new Container();
	rightPaddle->addComponent(new EmptyRectRC(build_sdlcolor(0x0000ffff)));
	rightPaddle->addComponent(new PaddleAIPhysics(ball));
	rightPaddle->addComponent(new SimpleMovePC());
	rightPaddle->addComponent(new StopOnBorderPC());

	rightPaddle->setWidth(10.0f);
	rightPaddle->setHeight(50.0f);
	rightPaddle->getPos().set(sdlutils().width() - 15,
			sdlutils().height() / 2 - 25);

	return rightPaddle;
}

GameObject* DefaultPingPongFacoty::createLeftPaddle(GameObject *ball) {

	Container *leftPaddle = new Container();
	leftPaddle->addComponent(new FilledRectRC(build_sdlcolor(0xff0000ff)));

	auto kbIC = new PaddleKBCtrlIC();
	kbIC->setKeys(SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A);
	leftPaddle->addComponent(kbIC);

	leftPaddle->addComponent(new SimpleMovePC());
	leftPaddle->addComponent(new StopOnBorderPC());

	leftPaddle->setWidth(10.0f);
	leftPaddle->setHeight(50.0f);
	leftPaddle->getPos().set(10, sdlutils().height() / 2 - 25);

	return leftPaddle;
}

GameObject* DefaultPingPongFacoty::createGameManager(GameObject *ball,
		GameObject *leftPaddle, GameObject *rightPaddle) {
	Container *gm = new GameManager(ball, leftPaddle, rightPaddle);
	gm->addComponent(new GameCtrlIC());
	gm->addComponent(new PingPongRulePC());
	gm->addComponent(new ScoreRC());
	gm->addComponent(new CtrlMsgRC());
	return gm;
}

GameObject* DefaultPingPongFacoty::createBall() {
	Container *ball = new Container();
	ball->addComponent(new FilledRectRC());
	ball->addComponent(new SimpleMovePC());
	ball->addComponent(new BounceOnBorderPC());
	ball->setWidth(10.0f);
	ball->setHeight(10.0f);
	ball->getPos().set(sdlutils().width() / 2 - 5, sdlutils().height() / 2 - 5);

	return ball;
}
