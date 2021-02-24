// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "PhysicsComponent.h"

class BounceOnBorderPC: public PhysicsComponent {
public:
	BounceOnBorderPC();
	virtual ~BounceOnBorderPC();
	void update(Container *c) override;
};

