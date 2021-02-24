// This file is part of the course TPV2@UCM - Samir Genaim

#include "PaddleMouseCtrlIC.h"

#include "Container.h"
#include "../sdlutils/InputHandler.h"

PaddleMouseCtrlIC::PaddleMouseCtrlIC() {
}

PaddleMouseCtrlIC::~PaddleMouseCtrlIC() {
}

void PaddleMouseCtrlIC::handleInput(Container *c) {
	if (ih().mouseMotionEvent())
		c->getPos().setY(ih().getMousePos().second);
}
