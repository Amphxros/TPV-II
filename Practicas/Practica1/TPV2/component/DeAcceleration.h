#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Transform.h"

class DeAcceleration : public Component {

public:

	DeAcceleration() {};
	DeAcceleration(double thrust);
	virtual ~DeAcceleration();

	virtual void init() override;
	virtual void update() override;

private:

	Transform* tr_;
	double thrust_;

};