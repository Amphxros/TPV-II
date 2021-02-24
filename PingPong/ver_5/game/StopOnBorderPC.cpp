// This file is part of the course TPV2@UCM - Samir Genaim

#include "StopOnBorderPC.h"

#include "../sdlutils/SDLUtils.h"
#include "Container.h"

StopOnBorderPC::StopOnBorderPC() {

}

StopOnBorderPC::~StopOnBorderPC() {
}

void StopOnBorderPC::update(Container *c) {
	auto &pos = c->getPos();
	auto &vel = c->getVel();
	auto height = c->getHeight();

	if (pos.getY() < 0) {
		pos.setY(0);
		vel.setY(0);
	} else if (pos.getY() + height > sdlutils().height()) {
		vel.setY(0);
		pos.setY(sdlutils().height() - height);
	}

}
