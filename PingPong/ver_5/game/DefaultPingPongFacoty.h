// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "PingPongFactory.h"

class DefaultPingPongFacoty: public PingPongFactory {
public:
	DefaultPingPongFacoty();
	virtual ~DefaultPingPongFacoty();
	GameObject* createRightPaddle(GameObject *ball) override;
	GameObject* createLeftPaddle(GameObject *ball) override;
	GameObject* createGameManager(GameObject *ball, GameObject *leftPaddle,
			GameObject *rightPaddle) override;
	GameObject* createBall() override;
};

