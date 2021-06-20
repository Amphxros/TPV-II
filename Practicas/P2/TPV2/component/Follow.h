#pragma once
#include "../ecs/Component.h"

class Transform;
class Follow : public Component {

public:

	Follow(Transform* tr, Transform* target);
	virtual ~Follow();

	void update();

private:
	Transform* tr_;
	Transform* target_;

};