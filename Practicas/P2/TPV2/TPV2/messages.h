#pragma once
#include <SDL_stdinc.h>

#include "GameCtrlSystem.h"
#include "utils/Vector2D.h"

struct Entity;

enum MsgType : Uint8 {
	_GAME_START_, //
	_GAME_OVER_, //
	_ROUND_START_, //
	_ROUND_OVER_,
	_SHOOT,
	_COLLISION_ASTEROID_BULLET,
	_COLLISION_FIGHTER_ASTEROID
};

struct CollidesWithEntity {
	Entity* entityA;
	Entity* entityB;
};

struct RoundInfo {
	Uint8 remainingRounds_;
	bool fighterWon_;
};
struct BulletInfo {
	Vector2D pos, vel;
	double w, h;
};

struct Message {
	MsgType type_;
	// Union types; solo se inicializa el que se va a usar
	union {
		CollidesWithEntity entity_;
		RoundInfo round_;
		BulletInfo bullet_;
	};
};