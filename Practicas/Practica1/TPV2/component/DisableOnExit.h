#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

class DisableOnExit : public Component {

public:

	DisableOnExit();
	virtual ~DisableOnExit();

	virtual void init() override;
	virtual void update() override;

private:

	Transform* tr_;

};