#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"

class ShowAtOppositeSide :	public Component{

public:

	ShowAtOppositeSide();
	virtual ~ShowAtOppositeSide();

	virtual void init() override;
	virtual void update() override;

private:

	Transform* tr_;

};