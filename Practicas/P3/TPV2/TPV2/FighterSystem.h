#pragma once

#include <SDL_stdinc.h>
#include "ecs/System.h"
#include "utils/Vector2D.h"

struct Entity;
struct Image;

class FighterSystem: public System
{
public: 
	FighterSystem();
	virtual ~FighterSystem(){}
	void init() override;
	void update();
	void resetFighters();
	void setFighterPosition(Uint8 id, Vector2D pos, float rotation);

protected:
	void moveFighter(Entity* e);
	Entity* fighterA;
	Entity* fighterB;

};
