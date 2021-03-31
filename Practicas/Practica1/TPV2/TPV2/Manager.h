#pragma once
#include "Entity.h"
#include "System.h"
#include <memory>
using uptr_ent = std::unique_ptr<Entity>;
class Manager
{
public:
	Manager():entities_(), handlers_() {};
	virtual ~Manager() {};

	Entity* addEntity();
	void refresh();		// Controla y borra las entidades no activas
	void update();		// Llamada a Update de entidades
	void render();		// Llamada a Render de entidades

	inline Entity* getHandler(ecs::GroupID id) {
		return handlers_[id];
	}

	inline void setHandler(Entity* e, ecs::GroupID id) {
		handlers_[id] = e;
	}


private:
	std::vector<uptr_ent> entities_;	// TODAS las entidades, uptr_ent ayuda a borrarlas automáticamente
	std::array<Entity*, ecs::maxGroups> handlers_;
};