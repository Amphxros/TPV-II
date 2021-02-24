// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "PhysicsComponent.h"

class SimpleMovePC: public PhysicsComponent {
public:
	SimpleMovePC();
	virtual ~SimpleMovePC();
	void update(Container *c) override;
};

