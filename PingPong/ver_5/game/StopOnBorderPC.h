// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "PhysicsComponent.h"

class StopOnBorderPC: public PhysicsComponent {
public:
	StopOnBorderPC();
	virtual ~StopOnBorderPC();
	void update(Container *c) override;
};

