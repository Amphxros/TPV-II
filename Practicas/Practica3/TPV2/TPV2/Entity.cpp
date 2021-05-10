#include "Entity.h"

Entity::Entity(Manager* mngr):
	active(true), mngr_(mngr), cmpArray_(), groups_()
{
}

Entity::~Entity()
{
	components_.clear();


}

void Entity::render()
{
	std::size_t size = components_.size();
	for (auto i = 0u; i < size ; i++)
		components_[i]->render();
}

void Entity::update()
{

	std::size_t size = components_.size();
	for (auto i = 0u; i < size ;i++)
		components_[i]->update();
}
