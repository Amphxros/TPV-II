// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <string>

#include "../json/JSON.h"
#include "PingPongFactory.h"

class Container;

class FilePingPongFactory: public PingPongFactory {
public:
	FilePingPongFactory(std::string file);
	virtual ~FilePingPongFactory();
	GameObject* createRightPaddle(GameObject *ball) override;
	GameObject* createLeftPaddle(GameObject *ball) override;
	GameObject* createGameManager(GameObject *ball, GameObject *leftPaddle,
			GameObject *rightPaddle) override;
	GameObject* createBall() override;

private:
	Container* createPaddle(JSONValue *jValue, GameObject *ball);
	JSONObject cfg_;
};

