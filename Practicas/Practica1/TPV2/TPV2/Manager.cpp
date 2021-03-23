#include "Manager.h"

Entity* Manager::addEntity() {

	Entity* e = new Entity(this);
	if (e != nullptr)
		entities_.emplace_back(e);
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

// Llama al Update de todas las entidades
void Manager::update()
{
	std::size_t n = entities_.size();
	for (int i = 0; i < n; i++)
		entities_[i]->update();
}

// Llama al Draw de todas las entidades
void Manager::render()
{
	std::size_t n = entities_.size();
	for (int i = 0; i < n; i++)
		entities_[i]->render();
}