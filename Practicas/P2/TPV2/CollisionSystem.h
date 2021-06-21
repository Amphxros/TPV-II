#pragma once
#include "ecs/System.h"
class Transform;
class CollisionSystem :	public System	{

public:

	CollisionSystem();
	virtual ~CollisionSystem(){}

	virtual void init() override;
	virtual void update() override;
	void receive(const msg::Message& m) override;

private:

	bool collides(Transform* a, Transform* b);

};