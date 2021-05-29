#pragma once
#include "ecs/System.h"
#include "utils/Vector2D.h"
class BulletsSystem: public System
{
public:
	BulletsSystem();
	virtual ~BulletsSystem(){}
	void init() override;
	void update() override;

	void shoot(Vector2D pos, Vector2D vel, double width, double height);
};

