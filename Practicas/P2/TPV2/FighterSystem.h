#pragma once

#include "ecs/System.h"

class FighterSystem :	public System{

public:

	FighterSystem();
	virtual ~FighterSystem();

	virtual void init() override;
	virtual void update() override;
	void receive(const msg::Message& m) override;

private:

	void onAsteroidCollision();
	bool active;

};