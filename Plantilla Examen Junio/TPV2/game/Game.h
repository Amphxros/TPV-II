// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <memory>



// when you are not using the methods of a class, just
// say that they exist, that saves time when parsing files
class Manager;
class System;

class Game {
public:
	Game();
	virtual ~Game();
	void init();
	void start();
private:
	std::unique_ptr<Manager> mngr_;
	System *collisionSys_;
	System *gameMngrSys_;
	System *pacmanSys_;
	System *ghostsSys_;
	System *foodSys_;
	System *soundSystem_;
	System *renderSys_;
};

