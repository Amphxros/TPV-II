// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/System.h"
#include "messages.h"

#include <SDL_stdinc.h>
#include <array>

struct Transform;

class GameManagerSystem: public System {
public:

	enum GameSate : Uint8 {
		NEWGAME = 0, // antes de empezar la primera ronda
		PAUSED,      // entre rondas
		RUNNING,     // en marcha
		GAMEOVER     // el juego ha acabdo
	};

	GameManagerSystem();
	virtual ~GameManagerSystem();

	Uint8 getState() {
		return state_;
	}

	void init() override;
	void update() override;
	void receive(const Message &msg) override;

private:

	void handlePacMancolliedsWithGhost(const Message &msg);
	void handleNoMoreFruit(const Message &msg);
	void chageState(GameSate state, Uint8 msgType, bool won = false);

	Uint8 state_;
	Uint8 remainingRounds_;
	Uint8 maxRounds_;

};

