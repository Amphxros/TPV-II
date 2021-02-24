// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <SDL.h>
#include "InputComponent.h"

class PaddleKBCtrlIC: public InputComponent {
public:
	PaddleKBCtrlIC();
	virtual ~PaddleKBCtrlIC();
	void handleInput(Container *c) override;

	inline void setKeys(SDL_Scancode up, SDL_Scancode down, SDL_Scancode stop) {
		up_ = up;
		down_ = down;
		stop_ = stop;
	}

	inline void setSpeed(float speed) {
		speed_ = speed;
	}

protected:
	SDL_Color color_;
	SDL_Scancode up_;
	SDL_Scancode down_;
	SDL_Scancode stop_;
	float speed_;

};
