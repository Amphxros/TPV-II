#pragma once
#include <memory>
#include <array>
#include "Component.h"
#include <vector>
#include "ecs.h"
#include <bitset>

class Manager;
class Entity
{
	using uptr_cmp = std::unique_ptr<Component>;
public:
	Entity() : active(true), paused_(false) {}
	Entity(Manager* mngr);
	virtual ~Entity();
	template<typename T, typename...Targs>
	inline T* addComponent(Targs&&...args) {
		T* t(new T(std::forward<Targs>(args)...));
		std::unique_ptr<Component> c(t);
 		components_.push_back(std::move(c));
		cmpArray_[t->getID()] = t;

		t->setEntity(this);
		t->init();
		return t;

	}

	template<typename T, typename ...Ts>
	void removeComponent(Component* c) {
		auto id = c->getID();
		if (cmpArray_[id] != nullptr) {
			Component* old_cmp = cmpArray_[id];
			cmpArray_[id] = nullptr;
			components_.erase(
				std::find_if(
					components_.begin(),
					components_.end(),
					[old_cmp](const uptr_cmp& c) {
						return c.get() == old_cmp;
					}));
		}
	}

	template<typename T>
	inline T* getComponent() {
		auto id = 0; //hacer un algo aqui
		return static_cast<T*>(cmpArray_[id]);
	}

	template<typename T, typename ...Ts>
	inline T* getComponent(ecs::CmpID id) {
		return static_cast<T*>(cmpArray_[id]);
	}

	template<typename T>
	inline bool hasComponent(ecs::CmpID id) {
		return cmpArray_[id] != nullptr;
	}

	inline void setGroup(ecs::GroupID id, bool state) {
		groups_[id] = state;
	}
	
	inline bool hasGroup(ecs::GroupID id) {
		return groups_[id];
	}

	inline void resetGroups() {
		groups_.reset();
	}

	inline bool isActive() { return active; }
	inline void setActive(bool act) { active = act; }

	void render();
	void update();

	inline Manager* getMngr() { return mngr_; }
	inline bool isPaused() { return paused_; }
	inline void setPause(bool pause) { paused_=pause; }

protected:
	Manager* mngr_;
	bool active, paused_;
	std::vector<uptr_cmp> components_;
	std::array<Component*, ecs::maxComponents> cmpArray_ = {};
	std::bitset<ecs::maxGroups> groups_;
};