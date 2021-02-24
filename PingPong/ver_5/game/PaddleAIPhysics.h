// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "PhysicsComponent.h"

class GameObject;
class Vector2D;

class PaddleAIPhysics: public PhysicsComponent {
public:
	PaddleAIPhysics(GameObject *ball);
	virtual ~PaddleAIPhysics();
	void update(Container *c) override;
private:
	bool ballComingTowardsPaddle(const Vector2D &pos);
	GameObject *ball_;
};

