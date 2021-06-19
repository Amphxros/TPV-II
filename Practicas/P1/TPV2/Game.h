#pragma once

#include <memory>
#include "ecs/Entity.h"
#include "sdlutils/SDLUtils.h"

class Manager;
class Game
{
public:

	Game();
	~Game();

	void init();
	void start();

private:

	void update();
	void render();

	std::unique_ptr<Manager> mngr_;

};

