// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/System.h"

class Texture;
struct Transform;

class PacManSystem: public System {
public:
	PacManSystem();
	virtual ~PacManSystem();
	void init() override;
	void receive(const Message&) override;
	void update() override;

private:

	void resetPacMan();
	bool active_;
	Texture *sprites_;
	Transform *pacmanTR_;
};

