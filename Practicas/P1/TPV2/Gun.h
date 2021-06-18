#pragma once
#include "ecs/Component.h"
#include "Transform.h"

class Gun :
    public Component
{
	public: 
	Gun(double time);
		virtual ~Gun();

		virtual void init() override;
		virtual void update() override;
		

	private:
		Transform* tr_;
		double time, lastCreatedTime;
};

