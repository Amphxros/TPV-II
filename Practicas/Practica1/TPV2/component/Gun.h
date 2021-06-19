#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Transform.h"

class Gun :public Component{

public:

	Gun(): time_(-1), lastCreatedTime(-1), tr_(nullptr) {};
	Gun(double time);
	virtual ~Gun();

	virtual void init() override;
	virtual void update() override;

private:

	Transform* tr_;
	double time_, lastCreatedTime;

};