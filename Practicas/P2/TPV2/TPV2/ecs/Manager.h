// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <initializer_list>
#include <vector>
#include <list>
#include <type_traits>

#include "ecs.h"
#include "Entity.h"
#include "System.h"
#include "../messages.h"

class Manager {
public:

	Manager();
	virtual ~Manager();

	void resetGroups(Entity *e) {
		e->groups_.reset();
	}

	
	// entities
	Entity* addEntity() {
		Entity *e = new Entity(this);
		if (e != nullptr) {
			resetGroups(e);
			e->active_ = true;
			entities_.emplace_back(e);
		}
		return e;
	}

	
	// handlers
	template<typename T>
	inline void setHandler(Entity *e) {
		hdlrs_[ecs::hdlrIdx<T>] = e;
	}

	template<typename T>
	inline Entity* getHandler() {
		return hdlrs_[ecs::hdlrIdx<T>];
	}

	inline const std::vector<Entity*>& getEnteties() {
		return entities_;
	}

	// systems
	template<typename T, typename ...Ts>
	inline T* addSystem(Ts &&...args) {
		T *s = new T(std::forward<Ts>(args)...);
		sys_[ecs::sysIdx<T>] = std::unique_ptr<System>(s);
		s->setMngr(this);
		s->init();
		return s;
	}

	template<typename T>
	inline T* getSystem() {
		return static_cast<T*>(sys_[ecs::sysIdx<T>].get());
	}

	// message
	void send(const Message &m) {
		// Message needs a clone method because we don't know what is the actual type, and
		// we need to make a copy
		msgsQueue_.emplace_back(m.clone());
	}

	//	// instead of having a clone method in the messages, we could use templates to
	//	// creat it directly. In this case we use mngr_->send<MessageType>(a1,a2,...)
	//	template<typename T, typename ...Ts>
	//	void send(Ts &&...args) {
	//		msgsQueue_.emplace_back(new T(std::forward<Ts>(args)...));
	//	}

	void flushMsgsQueue() {
		for (auto j = 0u; j < msgsQueue_.size(); j++) {
			Message *m = msgsQueue_[j];
			for (auto i = 0u; i < sys_.size(); i++) {
				if (sys_[i] != nullptr)
					sys_[i]->receive(*m);
			}
			delete m; // we delete the message that was created with msg.clone()

		}
		msgsQueue_.clear();

	}


	void refresh();

private:

	std::vector<Entity*> entities_;
	std::array<Entity*, ecs::maxHdlr> hdlrs_ = { };
	std::array<std::unique_ptr<System>, ecs::maxSystem> sys_ = { };

	std::vector<Message*> msgsQueue_;
};

