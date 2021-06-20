// This file is part of the course TPV2@UCM - Samir Genaim
#include "../Message.h"
#pragma once

class Manager;
struct Message;

class System {

public:

	virtual ~System() {
	}

	void setMngr(Manager *mngr) {
		manager_ = mngr;
	}

	virtual void init() {
	}

	virtual void update() {
	}

	virtual void receive(const msg::Message& m) {
	}

protected:

	Manager *manager_;

};