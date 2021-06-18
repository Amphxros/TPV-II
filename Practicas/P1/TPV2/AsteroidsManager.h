#pragma once
#include "ecs/Component.h"

class AsteroidsManager :
    public Component
{
public:
	AsteroidsManager();
	virtual ~AsteroidsManager();

	virtual void init() override;
	virtual void update() override;
private:
	double time_, lastCreatedTime_;

};

