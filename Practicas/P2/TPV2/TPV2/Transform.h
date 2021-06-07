#pragma once

#include "ecs/Component.h"
#include "utils/Vector2D.h"

class Transform : public Component {
public:
	Transform() :
		pos_(), vel_(), width_(), height_(), rotation_() {
	}

	Transform(Vector2D pos, Vector2D vel, float width, float height,
		float rotation) :
		pos_(pos), //
		vel_(vel), //
		width_(width), //
		height_(height), //
		rotation_(rotation) {
	}

	virtual ~Transform() {
	}

	Vector2D pos_;
	Vector2D vel_;
	float width_;
	float height_;
	float rotation_;
};