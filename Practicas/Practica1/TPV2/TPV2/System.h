#pragma once

#include "ecs.h"
#include <memory>
#include "Entity.h"
using uptr_ent = std::unique_ptr<Entity>;
class Manager;
class System
{
public:
	System(Manager* mngr, ecs::HandlerID id);
	virtual ~System() { }
	void setMngr(Manager *manager) {
	manager_ = manager;
	}
	inline ecs::HandlerID getID() { return id_; }
	
	void refresh();		// Controla y borra las entidades no activas
	Entity* addEntity();
	virtual void init() { }
	virtual void update() { }
	virtual void render() { }
protected:
	Manager *manager_;
	ecs::HandlerID id_;
	
	std::vector<uptr_ent> entities_;	// entidades que añado a este system
};



