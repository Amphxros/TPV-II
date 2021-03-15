#include "Component.h"
#include "Entity.h"

#include "sdlutils/InputHandler.h"

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
Image::Image(Texture* t):
	Component(ecs::Image), texture_(t), tr_(nullptr)
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

//COMPONETE HEALTH
Health::Health()
{
}
Health::Health(int num): 
	Component(ecs::Health),maxVidas_(num)
{
}
void Health::init()
{
	resetNumVidas();
}

//COMPONENTE GUN
Gun::Gun(): 
	time_(0), Component()
{
}

Gun::Gun(uint32_t time):
	Component(ecs::Gun),time_(time)
{
}

void Gun::init()
{
	tr_ = entity_->getComponent<Transform>();
}

void Gun::handleInput()
{
	auto& ih = *InputHandler::instance();
	if (ih.isKeyDown(SDLK_s)) {
		std::cout << "pum";
	}
}
//COMPONENTE FIGHTERCTRL
FighterCtrl::FighterCtrl():
	Component(ecs::FighterCtrl)
{
}

void FighterCtrl::init()
{
	tr_ = entity_->getComponent<Transform>();
}

void FighterCtrl::handleInput()
{
	auto& ih = *InputHandler::instance();
	if (ih.isKeyDown(SDLK_UP)) {
		std::cout << "up";
	}
	//else if(...)
	//else if(...)
	//else if(...)
}

//COMPONENTE SHOW AT OPPOSITE SIDE
ShowAtOppositeSide::ShowAtOppositeSide()
{
}

void ShowAtOppositeSide::update()
{
}
