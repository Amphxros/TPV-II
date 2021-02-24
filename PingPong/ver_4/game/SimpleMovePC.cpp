// This file is part of the course TPV2@UCM - Samir Genaim

#include "SimpleMovePC.h"

#include "Container.h"

SimpleMovePC::SimpleMovePC() {
}

SimpleMovePC::~SimpleMovePC() {
}

void SimpleMovePC::update(Container *c) {
	c->getPos().set(c->getPos() + c->getVel());
}
