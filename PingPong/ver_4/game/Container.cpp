// This file is part of the course TPV2@UCM - Samir Genaim

#include "Container.h"

Container::Container() {
}

Container::~Container() {
	for (auto o : inputC_)
		delete o;
	for (auto o : physicsC_)
		delete o;
	for (auto o : renderC_)
		delete o;
}

void Container::update() {
	for (auto o : physicsC_)
		o->update(this);
}

void Container::render() {
	for (auto o : renderC_)
		o->render(this);
}

void Container::handleInput() {
	for (auto o : inputC_)
		o->handleInput(this);
}
