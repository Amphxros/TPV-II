#include "Component.h"
#include "Entity.h"
#include "Manager.h"
#include "sdlutils/InputHandler.h"

//////////////
// TRANSFORM//
//////////////

Transform::Transform() :
	Component(ecs::Transform), pos_(Vector2D()), vel_(Vector2D()), w_(0), h_(0), rot_(0)
{
}

Transform::Transform(Vector2D pos, Vector2D vel, double width, double height, double rotation) :
	Component(ecs::Transform), pos_(pos), vel_(vel), w_(width), h_(height), rot_(rotation)
{
}

void Transform::update()
{
	pos_ = pos_ + vel_;
}

//////////////////
//DEACCELERATION//
//////////////////

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
	tr_ = entity_->getComponent<Transform>(ecs::Transform);
	assert(tr_ != nullptr);
}

void DeAcceleration::update()
{
	Vector2D vel = tr_->getVel() * deAccel_;
	tr_->setVel(vel);
}


/////////
//IMAGE//
/////////

Image::Image(Texture* t) :
	Component(ecs::Image), texture_(t), tr_(nullptr)
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
	assert(tr_ != nullptr && texture_ != nullptr);
}


///////////
// HEALTH//
///////////

Health::Health():Component(ecs::Health), maxVidas_(3), texture_(nullptr), num_(3)
{
}
Health::Health(int num) :
	Component(ecs::Health), maxVidas_(num), texture_(nullptr), num_(num)
{
	std::cout << getNumVidas() << std::endl;
}
void Health::init()
{
	texture_ = &sdlutils().images().at("fighter");
	assert(texture_ != nullptr);
}

void Health::render()
{
	for (int i = 0; i < num_; i++) {

		SDL_Rect dest;
		dest.x = 60 * i;
		dest.y = 50;
		dest.w = 50;
		dest.y = 50;

		texture_->render(dest);
	}
}

////////
// GUN//
////////
Gun::Gun() :
	time_(0), Component(ecs::Gun), tr_(nullptr), mngr_(nullptr), curr_time_(0),lastTime_(0)
{
}

Gun::Gun(uint32_t time) :
	Component(ecs::Gun), time_(time), tr_(nullptr), mngr_(nullptr),curr_time_(0), lastTime_(0)
{
}

void Gun::init()
{
	curr_time_ = sdlutils().currRealTime() - time_;
	mngr_ = entity_->getMngr();
	tr_ = entity_->getComponent<Transform>(ecs::Transform);
	assert(tr_ != nullptr);
}

void Gun::update()
{
	auto& ih = *InputHandler::instance();
	if (ih.isKeyDown(SDLK_SPACE)&& sdlutils().currRealTime() - lastTime_ >= time_) {
		curr_time_ = sdlutils().currRealTime();

		Entity* b = mngr_->addEntity();
	
		Vector2D pos = tr_->getPos() + Vector2D(tr_->getW() / 2.0f, tr_->getH() / 2.0f) - Vector2D(0.0f, tr_->getH() / 2.0f + 7.0f).rotate(tr_->getRotation()) - Vector2D(2.0f, 10.0f);

		Vector2D v = Vector2D(0, -1).rotate(tr_->getRotation()) * (tr_->getVel().magnitude() + 5.0f);

		b->addComponent<Transform>(pos, v, 5, 5, tr_->getRotation());
		b->addComponent <Image>(&sdlutils().images().at("Bullet"));
		b->addComponent<DisableOnExit>(sdlutils().width(), sdlutils().height());
		b->setGroup(ecs::BulletsGroup,true);
		mngr_->setHandler(b, ecs::BulletsHndlr);

		sdlutils().soundEffects().at("gunshot").play();
	}
}

///////////////
//FighterCtrl//
///////////////
FighterCtrl::FighterCtrl() :
	Component(ecs::FighterCtrl), tr_(nullptr), thrust_(0)
{
}

FighterCtrl::FighterCtrl(double thrust):
	Component(ecs::FighterCtrl), tr_(nullptr), thrust_(thrust)
{
}

void FighterCtrl::init()
{
	tr_ = entity_->getComponent<Transform>(ecs::Transform);
	pos_ini = tr_->getPos();
	assert(tr_ != nullptr);

}

void FighterCtrl::update()
{
	auto& ih = *InputHandler::instance();
	if (ih.isKeyDown(SDLK_UP)) {
		Vector2D vel = tr_->getVel();
		Vector2D newVel = vel + Vector2D(0, -1).rotate(tr_->getRotation()) * thrust_; 
		
		tr_->setVel(newVel);
		
		sdlutils().soundEffects().at("thrust").play();
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
		Vector2D newVel = vel + Vector2D(0, 1).rotate(tr_->getRotation()) * thrust_; 
		tr_->setVel(newVel);
		
		sdlutils().soundEffects().at("thrust").play();
	}
}

void FighterCtrl::resetPos()
{
	tr_->setPos(pos_ini);
	tr_->setVel(Vector2D());
}


//////////////////////////
// SHOW AT OPPOSITE SIDE//
//////////////////////////

ShowAtOppositeSide::ShowAtOppositeSide() : 
	Component(ecs::ShowAtOppositeSide), tr_(nullptr), width_(0), height_(0)
{
}

ShowAtOppositeSide::ShowAtOppositeSide(int width, int height) :
	Component(ecs::ShowAtOppositeSide), width_(width), height_(height), tr_(nullptr)
{
}

void ShowAtOppositeSide::init()
{
	tr_ = entity_->getComponent<Transform>(ecs::Transform);
	assert(tr_ != nullptr);
}

void ShowAtOppositeSide::update()
{
	//comprobamos en X
	if (tr_->getPos().getX() < 0) {
		tr_->setPos(Vector2D(width_, tr_->getPos().getY()));
	}
	else if (tr_->getPos().getX() > width_) {

		tr_->setPos(Vector2D(tr_->getW(), tr_->getPos().getY()));
	}
	// comprobamos en y
	if (tr_->getPos().getY() < 0) {

		tr_->setPos(Vector2D(tr_->getPos().getX(), height_));
	}
	else if (tr_->getPos().getY() > height_) {

		tr_->setPos(Vector2D(tr_->getPos().getX(), tr_->getH()));
	}
}

//////////////////
// FRAMED IMAGE //
//////////////////
FramedImage::FramedImage(Texture* texture, int nRows, int nCols, int posX, int posY, float framerate) :
	Component(ecs::FramedImage), texture_(texture), nRows_(nRows), nCols_(nCols), framerate_(framerate),pos_X(posX), pos_Y(posY), tr_(nullptr)
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
	if (((sdlutils().currRealTime()) % (int)framerate_) == 0) {

		if (pos_X + 1 == nCols_) {
			pos_X = 0;
		}
		else {
			pos_X++;
		}


		if (pos_Y + 1 == nRows_) {
			pos_Y = 0;
		}
		else {
			pos_Y++;
		}

		src_.x = pos_X * width;
		src_.y = pos_Y * height;
		src_.w = width;
		src_.h = height;

	}
}



/////////////////
// GENERATIONS //
/////////////////
Generations::Generations():
	maxgen_(0),gen_(0)
{
}

Generations::Generations(int gen): 
	Component(ecs::Generations), maxgen_(gen), gen_(gen)
{
}

void Generations::resetGen()
{
	gen_ = maxgen_;
}

DisableOnExit::DisableOnExit(int width, int height): 
	Component(ecs::DisableOnExit), width_(width), height_(height), tr_(nullptr)
{
}

///////////////////
// DISABLEONEXIT //
///////////////////
DisableOnExit::~DisableOnExit()
{
}

void DisableOnExit::init()
{
	tr_ = entity_->getComponent<Transform>(ecs::Transform);
	assert(tr_ != nullptr);
}

void DisableOnExit::update()
{
	//comprobamos en X
	if (tr_->getPos().getX() < 0) {
		entity_->setActive(false);
	}
	else if (tr_->getPos().getX() > width_) {
		entity_->setActive(false);
	}
	// comprobamos en y
	if (tr_->getPos().getY() < 0) {
		entity_->setActive(false);
	}
	else if (tr_->getPos().getY() > height_) {
		entity_->setActive(false);
	}

}


////////////
// FOLLOW //
////////////
Follow::Follow(): 
	Component(ecs::Follow), tr_(nullptr), posPlayer(nullptr)
{
}

void Follow::init()
{
	tr_ = entity_->getComponent<Transform>(ecs::Transform);
	assert(tr_ != nullptr);
	posPlayer = entity_->getMngr()->getHandler(ecs::FighterHndlr)->getComponent<Transform>(ecs::Transform);
	assert(posPlayer != nullptr);
}

void Follow::update()
{
	auto dir = tr_->getVel();
	Vector2D pos_ = tr_->getPos();
	dir.set(dir.rotate(dir.angle(posPlayer->getPos() - pos_) > 0 ? 1.0f : -1.0f));
	
	tr_->setVel(dir);
}

