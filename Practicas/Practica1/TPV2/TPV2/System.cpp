#include "System.h"

Entity* System::addEntity() {

	Entity* e = new Entity(manager_);
	if (e != nullptr)
		entities_.emplace_back(e);
	return e;

}


void System::refresh()
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
