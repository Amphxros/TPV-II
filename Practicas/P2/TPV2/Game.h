#pragma once

#include <memory>
#include "ecs/Entity.h"
#include "sdlutils/SDLUtils.h"

#include "AsteroidSystem.h"

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

};