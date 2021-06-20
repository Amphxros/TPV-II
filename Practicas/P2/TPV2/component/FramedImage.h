#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "../sdlutils/Texture.h"

class Transform;
class FramedImage : public Component {

public:

	FramedImage(): tex_(nullptr),dimX(0), dimY(0),posX(0), posY(0),lastTime(0), timer(0),dim(Vector2D()),src(){}
	FramedImage(Texture* tex, int rows, int cols, int r, int c, float frate=50.0f);
	virtual ~FramedImage();

	void update();

	SDL_Rect getSrc() { return src; }
	Texture* getTexture() { return tex_; }

private:

	SDL_Rect src;
	Texture* tex_;

	Vector2D iniFrame;
	Vector2D dim;


	float timer, lastTime;
	int dimX, dimY, posX, posY;

};