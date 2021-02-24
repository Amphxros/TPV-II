// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "PhysicsComponent.h"

#include "GameManager.h"

class PingPongRulePC: public PhysicsComponent {
public:
	PingPongRulePC();
	virtual ~PingPongRulePC();
	void update(Container *c) override;
private:
	void onBallExit(GameManager::Side side, GameManager *gm);

};

