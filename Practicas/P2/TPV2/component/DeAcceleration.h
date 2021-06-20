#pragma once
#include "../ecs/Component.h"

class Transform;
class DeAcceleration : public Component {

public:

	DeAcceleration() {};
	DeAcceleration(double thrust);
	virtual ~DeAcceleration();

	double getThrust() { return thrust_; }

private:

	Transform* tr_;
	double thrust_;

};