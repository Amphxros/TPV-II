#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"

class Image :	public Component{

public:

	Image() {};
	Image(Texture* tex);
	virtual ~Image();
	Texture* getTexture() { return tex_; }

private:
	Texture* tex_;

};