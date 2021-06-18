#pragma once
#include "ecs/Component.h"
#include "ecs/Entity.h"
#include "Transform.h"

class Follow : public Component {

public:

	Follow();
	virtual ~Follow();

	virtual void init() override;
	virtual void update() override;

private:

	Transform* tr_;
	Transform* target_;
	double thrust_;

};