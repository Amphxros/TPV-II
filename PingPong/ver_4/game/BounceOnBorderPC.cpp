// This file is part of the course TPV2@UCM - Samir Genaim

#include "BounceOnBorderPC.h"

#include "../sdlutils/SDLUtils.h"
#include "Container.h"

BounceOnBorderPC::BounceOnBorderPC() {
}

BounceOnBorderPC::~BounceOnBorderPC() {
}

void BounceOnBorderPC::update(Container *c) {
	auto &pos = c->getPos();
	auto &vel = c->getVel();
	auto height = c->getHeight();

	// bounce on top/bottom borders
	if (pos.getY() < 0) {
		pos.setY(0.0f);
		vel.setY(-vel.getY());
		sdlutils().soundEffects().at("wall_hit").play();
	} else if (pos.getY() + height > sdlutils().height()) {
		pos.setY(sdlutils().height() - height);
		vel.setY(-vel.getY());
		sdlutils().soundEffects().at("wall_hit").play();
	}
}
