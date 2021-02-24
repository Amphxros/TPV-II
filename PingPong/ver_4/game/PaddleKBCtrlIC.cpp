// This file is part of the course TPV2@UCM - Samir Genaim

#include "PaddleKBCtrlIC.h"

#include "../sdlutils/InputHandler.h"
#include "Container.h"

PaddleKBCtrlIC::PaddleKBCtrlIC() :
		up_(SDL_SCANCODE_UP), //
		down_(SDL_SCANCODE_DOWN), //
		stop_(SDL_SCANCODE_LEFT), //
		speed_(10.0f) //
{

}

PaddleKBCtrlIC::~PaddleKBCtrlIC() {
}

void PaddleKBCtrlIC::handleInput(Container *c) {
	auto &vel = c->getVel();
	if (ih().keyDownEvent()) {
		if (ih().isKeyDown(up_)) {
			vel.setY(-speed_);
		} else if (ih().isKeyDown(down_)) {
			vel.setY(speed_);
		} else if (ih().isKeyDown(stop_)) {
			vel.setY(0.0f);
		}
	}

}
