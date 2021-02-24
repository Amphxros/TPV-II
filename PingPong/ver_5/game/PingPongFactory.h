// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "GameObject.h"

class PingPongFactory {
public:
	PingPongFactory() {
	}
	virtual ~PingPongFactory() {
	}
	virtual GameObject* createBall() = 0;
	virtual GameObject* createLeftPaddle(GameObject *ball) = 0;
	virtual GameObject* createRightPaddle(GameObject *ball) = 0;
	virtual GameObject* createGameManager(GameObject *ball,
			GameObject *leftPaddle, GameObject *rightPaddle) = 0;
};

