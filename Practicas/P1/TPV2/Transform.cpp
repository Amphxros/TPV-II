#include "Transform.h"
#include <iostream>



Transform::Transform(Vector2D pos, Vector2D dir, double width, double height, double rotation): 
	Component(), pos_(pos), dir_(dir), w_(width), h_(height),rot_(rotation)
{
}

Transform::~Transform()
{
}

void Transform::init()
{
}

void Transform::update()
{
	pos_ = pos_ + dir_;
}
