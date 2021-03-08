#pragma once
#include <memory>
#include "Entity.h"

// Gestor de entidades generico; Los gestores especificos heredan de él (AsteroidsManager, CollisionManger...)
using uptr_ent = std::unique_ptr<Entity>;
class Manager
{
public:
	Manager();
	virtual ~Manager();

	Entity* addEntity();
	void refresh();		// Controla y borra las entidades no activas
	void update();		// Llamada a Update de entidades
	void render();		// Llamada a Render de entidades
	void handleInput();		// Llamada a Render de entidades
private:
	std::vector<uptr_ent> entities_;	// TODAS las entidades, uptr_ent ayuda a borrarlas automáticamente
};

