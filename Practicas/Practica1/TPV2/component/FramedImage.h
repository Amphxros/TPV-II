#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "../sdlutils/Texture.h"

class FramedImage : public Component {

public:

	FramedImage(): tr_(nullptr), tex_(nullptr),dimX(0), dimY(0),posX(0), posY(0),lastTime(0), timer(0),dim(Vector2D()),src(){}
	FramedImage(Texture* tex, int rows, int cols, int r, int c, float frate=50.0f);
	virtual ~FramedImage();

	virtual void init() override;
	virtual void update() override;
	virtual void render() override;

private:

	Transform* tr_;
	Texture* tex_;
	Vector2D iniFrame;
	Vector2D dim;

	SDL_Rect src;

	float timer, lastTime;
	int dimX, dimY, posX, posY;

};