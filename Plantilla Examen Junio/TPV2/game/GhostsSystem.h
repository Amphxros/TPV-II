// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/System.h"

#include <SDL_stdinc.h>

class Texture;
struct Transform;

class GhostsSystem: public System {
public:
	GhostsSystem();
	virtual ~GhostsSystem();
	void init() override;
	void receive(const Message&) override;
	void update() override;
private:

	void addGhost();
	void removeAllGhosts();

	bool active_;

	int currNumOfGhosts_;
	int maxNumOfGhosts_;

	Uint32 lastTimeCreatedGhosts_;
	Uint32 ghostCreationFrequency_;
	Texture *sprites_;
	Transform *pacmanTR_;

};
