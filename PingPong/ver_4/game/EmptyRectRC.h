// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL.h>

#include "RenderComponent.h"

class EmptyRectRC: public RenderComponent {
public:
	EmptyRectRC();
	EmptyRectRC(SDL_Color color);
	virtual ~EmptyRectRC();
	void render(Container *c) override;
private:
	SDL_Color color_;
};

