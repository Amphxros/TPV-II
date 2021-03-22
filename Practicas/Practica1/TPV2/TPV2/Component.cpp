#include "Component.h"
#include "Entity.h"

#include "sdlutils/InputHandler.h"

//COMPONENTE TRANSFORM
Transform::Transform() :
	Component(), pos_(Vector2D()), vel_(Vector2D()), w_(0), h_(0), rot_(0)
{
}

Transform::Transform(Vector2D pos, Vector2D vel, double width, double height, double rotation) :
	Component(), pos_(pos), vel_(vel), w_(width), h_(height), rot_(rotation)
{
}

void Transform::update()
{
	pos_ = pos_ + vel_;
}


//DEACCELERATION
DeAcceleration::DeAcceleration(double deAcceleration) :
	Component(), tr_(nullptr), deAccel_(deAcceleration)
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
Image::Image(Texture* t) :
	Component(), texture_(t), tr_(nullptr)
{
}

void Image::init()
{
	tr_ = entity_->getComponent<Transform>(ecs::Transform);
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
Health::Health(int num, Texture* texture) :
	Component(), maxVidas_(num), texture_(texture)
{
}
void Health::init()
{
	resetNumVidas();
}

void Health::render()
{

	for (int i = 0; i < num_; i++) {
		SDL_Rect dest;
		dest.x = i * 60;
		dest.y = 0;
		dest.w = 50;
		dest.y = 50;

		texture_->render(dest);
	}

}

//COMPONENTE GUN
Gun::Gun() :
	time_(0), Component()
{
}

Gun::Gun(uint32_t time) :
	Component(), time_(time)
{
}

void Gun::init()
{
	tr_ = entity_->getComponent<Transform>(ecs::Transform);
	assert(tr_ != nullptr);
}

void Gun::update()
{
	auto& ih = *InputHandler::instance();
	if (ih.isKeyDown(SDLK_s)) {
		std::cout << "pum";
	}
}


//COMPONENTE FIGHTERCTRL
FighterCtrl::FighterCtrl() :
	Component(), tr_(nullptr)
{
}

void FighterCtrl::init()
{
	tr_ = entity_->getComponent<Transform>(ecs::Transform);
	assert(tr_ != nullptr);
}

void FighterCtrl::update()
{
	auto& ih = *InputHandler::instance();
	if (ih.isKeyDown(SDLK_UP)) {
		Vector2D vel = tr_->getVel();
		Vector2D newVel = vel + Vector2D(0, -1).rotate(tr_->getRotation()) * 0.2; //cambiar el 0.2 por 1 parametro
		std::cout << "up";
	}
	else if (ih.isKeyDown(SDLK_LEFT)) {
		double r = tr_->getRotation() - 5.0;
		tr_->setRotation(r);
	}
	else if (ih.isKeyDown(SDLK_RIGHT)) {
		double r = tr_->getRotation() + 5.0;
		tr_->setRotation(r);
	}
	else if (ih.isKeyDown(SDLK_DOWN)) {
		Vector2D vel = tr_->getVel();
		Vector2D newVel = vel + Vector2D(0, 1).rotate(tr_->getRotation()) * 0.2; //cambiar el 0.2 por 1 parametro

	}
}


//COMPONENTE SHOW AT OPPOSITE SIDE
ShowAtOppositeSide::ShowAtOppositeSide() : Component()
{
}

ShowAtOppositeSide::ShowAtOppositeSide(int width, int height) :
	Component(), width_(width), height_(height), tr_(nullptr)
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

		tr_->setPos(Vector2D(tr_->getPos().getX(), height_));
	}
	else if (tr_->getPos().getX() + tr_->getH() > height_) {

		tr_->setPos(Vector2D(tr_->getPos().getX(), tr_->getH()));
	}
}

FramedImage::FramedImage(Texture* texture, int nRows, int nCols, int posX, int posY, float framerate) :
	Component(), texture_(texture), nRows_(nRows), nCols_(nCols), framerate_(framerate),
	pos_X(posX), pos_Y(posY), tr_(nullptr)
{
	width = texture_->width() / nCols_;
	height = texture_->height() / nRows_;

	src_.x = pos_X * width;
	src_.y = pos_Y * height;
	src_.w = width;
	src_.h = height;

	tam = Vector2D(nCols_, nRows_);
	ini = Vector2D(pos_X, pos_Y);

}

FramedImage::~FramedImage()
{
}

void FramedImage::init()
{
	tr_ = entity_->getComponent<Transform>(ecs::Transform);
	assert(tr_ != nullptr);
}

void FramedImage::render()
{
	SDL_Rect dest;
	dest.x = tr_->getPos().getX();
	dest.y = tr_->getPos().getY();
	dest.w = tr_->getW();
	dest.h = tr_->getH();

	texture_->render(src_, dest, tr_->getRotation());

}

void FramedImage::update()
{

}
