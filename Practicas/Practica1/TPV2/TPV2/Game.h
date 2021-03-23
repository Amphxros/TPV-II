#pragma once
class Manager;
class Game
{
public:
	Game();
	void init();
	void update();
	void render();

private:
	Manager* mngr_;
};

