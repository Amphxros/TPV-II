#pragma once
#include "Entity.h"
#include "System.h"
#include <memory>
using uptr_ent = std::unique_ptr<Entity>;
class Manager
{
public:
	Manager():entities_(), sys_() {};
	virtual ~Manager() {};

	Entity* addEntity();
	void refresh();		// Controla y borra las entidades no activas
	void update();		// Llamada a Update de entidades
	void render();		// Llamada a Render de entidades
	
	template<typename T, typename ...Ts>
	inline T* addSystem(Ts &&...args) {
	 T *s = new T(std::forward<Ts>(args)...);
	 sys_[s->getID()] = std::unique_ptr<System>(s);
	 s->setMngr(this);
	 s->init();
	 return s;
	 }

	template<typename T>
	inline T* getSystem(ecs::SystemID id) {
	 return static_cast<T*>(sys_[id].get());
	}



private:
	std::vector<uptr_ent> entities_;	// TODAS las entidades, uptr_ent ayuda a borrarlas automáticamente
	std::array<std::unique_ptr<System>, ecs::maxSystem> sys_; //array de sistemas
};