// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "Component.h"

class InputComponent: public Component {
public:
	InputComponent() {
	}
	virtual ~InputComponent() {
	}
	virtual void handleInput(Container *c) = 0;
};
