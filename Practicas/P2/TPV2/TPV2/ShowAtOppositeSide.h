#pragma once
#include "ecs/Component.h"
class ShowAtOppositeSide :
	public Component
{
public :
	ShowAtOppositeSide() {}
	virtual ~ShowAtOppositeSide() {}

	virtual void init() override {};
	virtual void update() override;
};

