#pragma once
#include "ecs/Component.h"
#include "Transform.h"

class FighterCtrl :
	public Component
{
public:
	FighterCtrl();
	virtual ~FighterCtrl();
	virtual void init() override;
	virtual void update() override;

private:
	Transform* tr_;
};

