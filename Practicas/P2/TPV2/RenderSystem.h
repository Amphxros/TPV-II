#pragma once
#include "ecs/System.h"
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

	


};

