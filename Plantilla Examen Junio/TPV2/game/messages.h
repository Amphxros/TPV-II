// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_stdinc.h>

#include "GameManagerSystem.h"

struct Entity;

enum MsgType : Uint8 {
	_GAME_START_, //
	_GAME_OVER_, //
	_ROUND_START_, //
	_ROUND_OVER_, //
	_PACMAN_COLLIDES_WITH_FOOD_, //
	_PACMAN_COLLIDES_WITH_GHOST_, //
	_NO_MORE_FRUIT_
};

struct ColliedsWithFood {
	Entity *entity_;
};

struct ColliedsWithGhost {
	Entity *entity_;
};

struct RoundInfo {
	Uint8 remainingRounds_;
	bool pacmanWon_;
};

struct Message {
	MsgType type_;
	union {
		ColliedsWithFood food_;
		ColliedsWithGhost ghost_;
		RoundInfo round_;
	};
};
