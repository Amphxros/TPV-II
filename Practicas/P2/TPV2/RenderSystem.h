#pragma once
#include "ecs/System.h"
#include "sdlutils/Texture.h"
class RenderSystem :
	public System
{
public:
	RenderSystem();
	virtual ~RenderSystem();

	virtual void init() override;
	virtual void update() override;
	virtual void receive(const msg::Message& m) override;
private:
	void renderAsteroids();
	void renderBullets();
	void renderFighter();
	void renderRemainingLives();
	void renderMsgs();

	Texture* initMsg;
	Texture* pauseMsg;
	Texture* gameOverMsg;
	Texture* gameWinMsg;

	int currState;


};

