// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL.h>

#include "RenderComponent.h"

class FilledRectRC: public RenderComponent {
public:
	FilledRectRC();
	FilledRectRC(SDL_Color color);
	virtual ~FilledRectRC();
	void render(Container *c) override;
private:
	SDL_Color color_;
};

