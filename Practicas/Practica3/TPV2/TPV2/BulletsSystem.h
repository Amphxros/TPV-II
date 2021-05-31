#pragma once
#include "ecs/System.h"
#include "utils/Vector2D.h"

struct Image;
struct Transform;
class BulletsSystem: public System
{
public:
	BulletsSystem();
	virtual ~BulletsSystem(){}
	void update() override;


	void resetBullets();
	void shoot(Vector2D pos, Vector2D vel, double width, double height);
};

