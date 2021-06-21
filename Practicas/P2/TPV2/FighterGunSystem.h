#pragma once
#include "ecs/System.h"

class Transform;
class FighterGunSystem :public System{

public:

	FighterGunSystem(double time);
	virtual ~FighterGunSystem();
	virtual void init() override;
	virtual void update() override;
	void receive(const msg::Message& m) override;

private:

	bool active;
	double time_, lastCreatedTime;
	Transform* tr_; //transform del fighter

};