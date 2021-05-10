#pragma once
#include "Entity.h"
#include <memory>
#include "System.h"
class Manager
{
public:
	Manager():entities_(), handlers_(), systems_() {};
	virtual ~Manager() {};

	Entity* addEntity();
	void refresh();		// Controla y borra las entidades no activas
	void update();		// Llamada a Update de entidades
	void render();		// Llamada a Render de entidades

	void resetGame();
	void PauseGame(bool act);

	inline Entity* getHandler(ecs::HandlerID id) {
		return handlers_[id];
	}

	inline void setHandler(Entity* e, ecs::HandlerID id) {
		handlers_[id] = e;
	}
	
	//devuelve las entidades
	inline std::vector<Entity*> getEntities() { return entities_; }
	template<typename T, typename ...Ts>
	inline T* getSystem(ecs::SystemID id) {
		return static_cast<T*>(systems_[id]);
	}
	inline void addSystem(System* sys,ecs::SystemID id) {
		systems_[id] = sys;
	}


private:
	std::vector<Entity*> entities_;	// TODAS las entidades
	std::array<Entity*, ecs::maxHandlers> handlers_; //handlers

	std::array<System*,ecs::maxSystems> systems_;	// los sistemas
};