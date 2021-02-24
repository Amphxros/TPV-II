// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <array>
#include "Container.h"

class GameManager: public Container {
public:

	enum Side {
		LEFT = 0, //
		RIGHT
	};
	
	enum GameSate {
		NEWGAME = 0, // just before starting a new game
		PAUSED, // between rounds
		RUNNING, // playing
		GAMEOVER // game over
	};

	GameManager(GameObject *b, GameObject *left, GameObject *right);
	virtual ~GameManager();

	inline std::array<unsigned int, 2>& getScore() {
		return score_;
	}

	inline GameSate& getState() {
		return state_;
	}

	inline unsigned int getMaxScore() {
		return maxScore_;
	}

	inline GameObject* getBall() {
		return ball_;
	}

	inline GameObject* getLeftPaddle() {
		return leftPaddle_;
	}

	inline GameObject* getRightPaddle() {
		return rightPaddle_;
	}
private:
	std::array<unsigned int, 2> score_;
	GameSate state_;
	const unsigned int maxScore_;
	GameObject *ball_;
	GameObject *leftPaddle_;
	GameObject *rightPaddle_;
};

