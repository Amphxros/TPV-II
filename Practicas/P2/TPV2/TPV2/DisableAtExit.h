#pragma once
#include "ecs/Component.h"
class DisableAtExit: public Component
{
public:
	DisableAtExit() {};
	virtual ~DisableAtExit() {};

	virtual void update() override;
};

