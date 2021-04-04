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
		std::remove_if( entities_.begin(),entities_.end(), [](Entity* & e) 
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
	for (int i = 0; i < n; i++) {
	if(!entities_[i]->isPaused())
		entities_[i]->update();
	}
}

// Llama al render de todas las entidades
void Manager::render()
{
	std::size_t n = entities_.size();
	for (int i = 0; i < n; i++)
		entities_[i]->render();
}

void Manager::PauseGame(bool act)
{
	for (Entity* e : entities_) {
		if (e->hasGroup(ecs::AsteroidsGroup) || e->hasGroup(ecs::Fighter)) {
			e->setPause(act);
		}
	}
}
void Manager::resetGame() {

	for (Entity* e : entities_) {
		if (e->hasGroup(ecs::AsteroidsGroup)) {
			e->setActive(false);
		}
	}
}