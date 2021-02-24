// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "Component.h"

class RenderComponent: public Component {
public:
	RenderComponent() {
	}

	virtual ~RenderComponent() {
	}
	virtual void render(Container *c) = 0;

};

