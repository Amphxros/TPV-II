// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/System.h"

class SoundEffect;

class SoundSystem: public System {
public:
	SoundSystem();
	virtual ~SoundSystem();
	void init() override;
	void receive(const Message&) override;
	void update() override;
private:
	SoundEffect *chompSound_;
	SoundEffect *deathSound_;
	SoundEffect *eatSound_;
	SoundEffect *introSound_;
	SoundEffect *wonSound_;
};

