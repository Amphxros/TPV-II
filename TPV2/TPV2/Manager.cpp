#include "Manager.h"

Manager::Manager() {

}

Manager::~Manager()
{
}

Entity* Manager::addEntity()
{
	Entity* e = new Entity(this);	// Creacion
	if (e != nullptr)
		entities_.emplace_back(e);	// Añadimos a la lista
	return e;
}

void Manager::refresh()
{
	entities_.erase(
	// Cambia los elementos inactivos al final del vector y devuelve su inicio
		std::remove_if( entities_.begin(),entities_.end(), [](const uptr_ent& e) 
			{
				return !e->isActive();
			}
			// A partir del puntero borra todos los elementos (Los que ya sabemos que son inactivos)
		),entities_.end());
}

void Manager::update()
{
	std::size_t n = entities_.size();
	for (int i = 0; i < n; i++)
		entities_[i]->update();
}

void Manager::render()
{
	std::size_t n = entities_.size();
	for (int i = 0; i < n; i++)
		entities_[i]->render();
}

void Manager::handleInput()
{
	std::size_t n = entities_.size();
	for (int i = 0; i < n; i++)
		entities_[i]->handleInput();
}
