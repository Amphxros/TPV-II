#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"

class Transform;
class ShowAtOppositeSide :	public Component{

public:
	ShowAtOppositeSide(Transform* tr);
	virtual ~ShowAtOppositeSide() {};

	void update();

private:

	Transform* tr_;

};