#pragma once

#include <memory>
#include "ecs/Entity.h"
#include "sdlutils/SDLUtils.h"

#include "AsteroidSystem.h"
#include "FighterSystem.h"
#include "BulletsSystem.h"
#include "GameCtrlSystem.h"
#include "RenderSystem.h"
#include "CollisionSystem.h"
#include "FighterGunSystem.h"
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
	AsteroidSystem* astSys_;
	BulletsSystem* bulletSys_;
	CollisionSystem* collisionSys_;
	GameCtrlSystem* gameSys_;

	FighterSystem* fighterSys_;
	FighterGunSystem* fighterGunSys_;
	RenderSystem* renderSys_;


};