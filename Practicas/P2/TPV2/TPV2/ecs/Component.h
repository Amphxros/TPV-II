// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
class Entity;
class Component {
public:
	Component(): entity_(nullptr){

	}
	virtual ~Component() {
	}

	virtual void init(){

	}
	virtual void update(){

	}

	inline void setEntity(Entity* e) {
		entity_ = e;
	}

	inline Entity* getEntity() {
		return entity_;
	}
protected:
	Entity* entity_;
};

