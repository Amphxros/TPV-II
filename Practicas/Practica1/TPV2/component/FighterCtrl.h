#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Transform.h"

class FighterCtrl :	public Component{

public:

	FighterCtrl(float speed, float thrust, float maxSpeed);
	virtual ~FighterCtrl();
	virtual void init() override;
	virtual void update() override;
	
private:

	Transform* tr_;
	float speed_, maxSpeed_,thrust_;

};

