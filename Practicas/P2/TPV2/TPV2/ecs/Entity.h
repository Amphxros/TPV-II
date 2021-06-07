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

		if (cmpArray_[id] != nullptr) {
			removeComponent<T>();
		}

		cmpArray_[id] = c;
		cmps_.emplace_back(c);

		return c;
	}

	template<typename T>
	void removeComponent() {
		auto id = ecs::cmpIdx<T>;
		if (cmpArray_[id] != nullptr) {
			Component* old_cmp = cmpArray_[id];
			cmpArray_[id] = nullptr;
			cmps_.erase( //
				std::find_if( //
					cmps_.begin(), //
					cmps_.end(), //
					[old_cmp](const Component* c) { //
						return c == old_cmp;
					}));
			delete old_cmp;
		}
	}

	template<typename T>
	inline T* getComponent() {
		auto id = ecs::cmpIdx<T>;
		return static_cast<T*>(cmpArray_[id]);
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
