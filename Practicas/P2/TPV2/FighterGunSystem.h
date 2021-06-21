#pragma once
#include "ecs/System.h"
class FighterGunSystem :
	public System
{
public:
	FighterGunSystem();
	virtual ~FighterGunSystem();
	virtual void init() override;
	virtual void update() override;
	void receive(const msg::Message& m) override;
private:
	bool active;
};

