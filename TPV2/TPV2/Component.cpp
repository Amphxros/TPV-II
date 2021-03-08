#include "Component.h"
#include "Entity.h"

//COMPONENTE TRANSFORM
Transform::Transform():
Component(ecs::Transform), pos_(Vector2D()), vel_(Vector2D()), w_(0), h_(0), rot_(0)
{
}

Transform::Transform(Vector2D pos, Vector2D vel, double width, double height, double rotation):
	Component(ecs::Transform), pos_(pos), vel_(vel), w_(width), h_(height), rot_(rotation)
{
}

void Transform::update()
{
	pos_ = pos_ + vel_;
}

//COMPONENTE IMAGE
Image::Image(Texture* t, Transform* tr):
	Component(ecs::Image), texture_(t), tr_(tr)
{
}

void Image::init()
{
	tr_ = entity_->getComponent<Transform>();
}

void Image::render()
{
	SDL_Rect dest;
	dest.x = tr_->getPos().getX();
	dest.y = tr_->getPos().getY(); 
	dest.w = tr_->getW();
	dest.h = tr_->getH();

	texture_->render(dest, tr_->getRotation());
}
