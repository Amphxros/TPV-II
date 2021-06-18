#pragma once
#include "ecs/Component.h"
#include "ecs/Entity.h"
#include "Transform.h"

class Gun :public Component{

public:

	Gun() {};
	Gun(double time);
	virtual ~Gun();

	virtual void init() override;
	virtual void update() override;

private:

	Transform* tr_;
	double time, lastCreatedTime;

};