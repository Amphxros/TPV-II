// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <array>
#include <bitset>
#include <memory>

#include "Component.h"
#include "ecs.h"

class Manager;

class Entity {

	friend Manager;

public:
	Entity(Manager* mngr) :
		active_(true), //
		mngr_(mngr), //
		cmps_(), //
		groups_() //
	{
	}


	virtual ~Entity() {
		for (auto it = cmps_.begin(); it != cmps_.end(); ++it) {
			auto aux = &it;
			delete aux;

		}
	}

	inline void setManager(Manager* m) { mngr_ = m; }
	inline Manager* getManager() { return mngr_; }

	template<typename T, typename ...Ts>
	T* addComponent(Ts&&... args) {
		T* c = new T(std::forward<Ts>(args)...);
		c->setEntity(this);
		c->init();
		constexpr auto id = ecs::cmpIdx<T>;

		if (cmps_[id] != nullptr) {
			removeComponent<T>();
		}

		cmps_[id] = c;

		return c;
	}

	template<typename T>
	void removeComponent() {
		auto id = ecs::cmpIdx<T>;
		if (cmps_[id] != nullptr) {
			Component* old_cmp = cmps_[id];
			cmps_[id] = nullptr;
		}
	}

	template<typename T>
	inline T* getComponent() {
		auto id = ecs::cmpIdx<T>;
		return static_cast<T*>(cmps_[id]);
	}
	inline bool isActive() const {
		return active_;
	}

	inline void setActive(bool state) {
		active_ = state;
	}

	template<typename T>
	inline bool hasGroup() {
		return groups_[ecs::grpIdx<T>];
	}

	template<typename T>
	inline void setGroup(bool state) {
		groups_[ecs::grpIdx<T>] = state;
	}

	inline void resetGroups() {
		groups_.reset();
	}


	void update() {
		std::size_t n = cmps_.size();
		for (auto i = 0u; i < n; i++) {
			cmps_[i]->update();
		}
	}

private:
	Manager* mngr_;
	bool active_;
	std::array<std::unique_ptr<Component>, ecs::maxComponent> cmps_ = { };
	std::bitset<ecs::maxGroup> groups_;
};
