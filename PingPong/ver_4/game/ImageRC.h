// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "RenderComponent.h"

#include "../sdlutils/Texture.h"

class ImageRC: public RenderComponent {
public:
	ImageRC(Texture *img);
	virtual ~ImageRC();
	void render(Container *c) override;

private:
	Texture *img_;
};

