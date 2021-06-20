// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/System.h"

struct Transform;
class SoundEffect;

class CollisionSystem: public System {
public:
	CollisionSystem();
	virtual ~CollisionSystem();
	void init() override;
	void update() override;
	void receive(const Message&) override;

private:
	bool collieds(Transform *tr1, Transform *tr2);
	bool active_;

	Transform *pacmanTr_;
};

