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


//DEACCELERATION
DeAcceleration::DeAcceleration(double deAcceleration) :
	Component(ecs::DeAcceleration), tr_(nullptr), deAccel_(deAcceleration)
{
}

DeAcceleration::~DeAcceleration()
{
	tr_ = nullptr;
}

void DeAcceleration::init()
{
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void DeAcceleration::update()
{
	Vector2D vel = tr_->getVel() * deAccel_;
	tr_->setVel(vel);
}



//COMPONENTE IMAGE
Image::Image(Texture* t):
	Component(ecs::Image), texture_(t), tr_(nullptr)
{
}

void Image::init()
{
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
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

void Health::render()
{
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
	Component(ecs::FighterCtrl),tr_(nullptr)
{
}

void FighterCtrl::init()
{
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
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
ShowAtOppositeSide::ShowAtOppositeSide(): Component(ecs::ShowAtOppositeSide)
{
}

ShowAtOppositeSide::ShowAtOppositeSide(int width, int height): 
	Component(ecs::ShowAtOppositeSide), width_(width), height_(height), tr_(nullptr)
{
}

void ShowAtOppositeSide::init()
{
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void ShowAtOppositeSide::update()
{
	//comprobamos en X
	if (tr_->getPos().getX() < 0) {
		tr_->setPos(Vector2D(width_, tr_->getPos().getY()));
	}
	else if (tr_->getPos().getX() + tr_->getW() > width_) {

		tr_->setPos(Vector2D(tr_->getW(), tr_->getPos().getY()));
	}
	// comprobamos en y
	if (tr_->getPos().getY() < 0) {

		tr_->setPos(Vector2D(tr_->getPos().getX(),height_));
	}
	else if (tr_->getPos().getX() + tr_->getH() > height_) {

		tr_->setPos(Vector2D(tr_->getPos().getX(), tr_->getH()));
	}
}

FramedImage::FramedImage(Texture* texture, int nRows, int nCols, int posX, int posY, float framerate): 
	Component(ecs::FramedImage), texture_(texture), nRows_(nRows), nCols_(nCols),framerate_(framerate),
	pos_X(posX),pos_Y(posY), tr_(nullptr)
{
	width = texture_->width() / nCols_;
	height = texture_->height() / nRows_;

	src_.x = pos_X* width;
	src_.y = pos_Y* height;
	src_.w = width;
	src_.h = height;

	tam = Vector2D(nCols_, nRows_);



}

void FramedImage::init()
{
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void FramedImage::render()
{
	SDL_Rect dest;
	dest.x = tr_->getPos().getX();
	dest.y = tr_->getPos().getY();
	dest.w = tr_->getW();
	dest.h = tr_->getH();

}

void FramedImage::update()
{
}
