#pragma once
#include "ecs/Component.h"
#include <SDL.h>
struct FighterCtrl : Component
{
	FighterCtrl(SDL_Scancode up, SDL_Scancode down, SDL_Scancode left, SDL_Scancode right,
		float speed):
		up_(up), //
		down_(down), //
		left_(left), //
		right_(right),
		speed_(speed) {
	}

	SDL_Scancode up_;
	SDL_Scancode down_;
	SDL_Scancode left_;
	SDL_Scancode right_;
	float speed_;
};

