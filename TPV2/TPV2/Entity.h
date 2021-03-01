#pragma once
#include <memory>
#include <array>
#include "Component.h"
#include <vector>
#include "ecs.h"

class Entity
{
	using uptr_cmp = std::unique_ptr<Component>;
public:
	template<typename T, typename ...Ts>
	inline T* addComponent(Ts&&...args) {
		
		T* c = new T(std::forward<Ts>(args));
		auto id = c->getID();
			if (cmpArray_[id] != nullptr) {
				//removeComponent<T>();
			}
		components_.emplace_back(c);
		
		cmpArray_[id] = c;
		c->setEntity(this);
		c->init();



		return c;
	}

	void removeComponent(Component* c) {

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
	inline bool hasComponent() {
		auto id = 0; //aqui deberia ir algo?
			return cmpArray_[id] != nullptr;
	}



protected:
		std::vector<uptr_cmp> components_;
		std::array<Component*, ecs::maxComponents> cmpArray_ = {};
};

