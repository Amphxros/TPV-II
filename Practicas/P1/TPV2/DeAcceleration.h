#pragma once
#include "ecs/Component.h"
#include "Transform.h"
class DeAcceleration :
    public Component
{
	public:
		DeAcceleration(double thrust);
		virtual ~DeAcceleration();

		virtual void init() override;
		virtual void update() override;
		

	private:
		Transform* tr_;
		double thrust_;
};
