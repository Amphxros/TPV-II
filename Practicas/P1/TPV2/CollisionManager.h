#pragma once
#include "ecs/Component.h"
class CollisionManager :
    public Component
{
public:
	CollisionManager();
	virtual ~CollisionManager();

	virtual void init() override;
	virtual void update() override;
};

