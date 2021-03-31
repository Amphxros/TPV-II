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

	inline void setHandler(Entity* e, ecs::HandlerID id) {
		handlers_[id] = e;
	}

	inline std::vector<Entity*> getEntities() { return entities_; }

private:
	std::vector<Entity*> entities_;	// TODAS las entidades, uptr_ent ayuda a borrarlas automáticamente
	std::array<Entity*, ecs::maxHandlers> handlers_;
};