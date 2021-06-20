#pragma once

#include <memory>
#include "ecs/Entity.h"
#include "sdlutils/SDLUtils.h"

#include "AsteroidSystem.h"
#include "FighterSystem.h"
#include "BulletsSystem.h"
#include "GameCtrlSystem.h"
#include "RenderSystem.h"

class Manager;
class Game
{
public:

	Game();
	~Game();

	void init();
	void start();

private:

	std::unique_ptr<Manager> mngr_;
	AsteroidSystem* astSys;
	BulletsSystem* bulletSys_;
	GameCtrlSystem* gameSys_;
	FighterSystem* fighterSys_;
	RenderSystem* renderSys_;

};