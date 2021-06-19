#pragma once
#include "../ecs/Component.h"
#include "State.h"
#include "AsteroidsManager.h"

class GameCtrl :public Component{

public:

	GameCtrl();
	virtual ~GameCtrl();

	virtual void init() override;
	virtual void update() override;

private:

	State* gameState_;
	AsteroidsManager* astManager;
	
};

