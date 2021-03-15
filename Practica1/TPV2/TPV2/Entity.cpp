#include "Entity.h"
#include "Manager.h"

Entity::Entity(Manager* mngr):
	mngr_(mngr), active(true)
{
}

Entity::~Entity()
{
}

void Entity::render()
{
	for (auto c : cmpArray_) {
		c->render();
	}
}

void Entity::update()
{
	for (auto c : cmpArray_) {
		c->update();
	}
}

void Entity::handleInput()
{
	for (auto c : cmpArray_) {
		c->handleInput();
	}
}
