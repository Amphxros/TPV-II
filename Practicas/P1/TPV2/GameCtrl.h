#pragma once
#include "ecs/Component.h"
#include "sdlutils/Texture.h"
#include "State.h"

class GameCtrl :
    public Component
{
	GameCtrl();
	virtual ~GameCtrl();

	virtual void init() override;
	virtual void update() override;
	virtual void render() override;

private:
	State* gameState_;
	Texture* initMsg;
	Texture* pauseMsg;
	Texture* gameOverMsg;
	

};

