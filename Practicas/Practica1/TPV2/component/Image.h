#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"

class Image :	public Component{

public:

	Image() {};
	Image(Texture* tex);
	virtual ~Image();

	virtual void init() override;
	virtual void render() override;

private:

	Transform* tr_;
	Texture* tex_;

};