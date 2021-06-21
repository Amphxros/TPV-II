#include "FighterGunSystem.h"
#include "ecs/Manager.h"
#include "sdlutils/SDLUtils.h"
#include "sdlutils/InputHandler.h"
#include "component/Transform.h"
FighterGunSystem::FighterGunSystem(double time):System(), active(false), time_(time)
{
}

FighterGunSystem::~FighterGunSystem()
{
}

void FighterGunSystem::init()
{
	Entity* e = manager_->getHandler<Fighter>();
	lastCreatedTime = sdlutils().currRealTime();
	tr_ = manager_->getComponent<Transform>(e);
	assert(tr_ != nullptr);
}

void FighterGunSystem::update()
{
	if (active) {
		if (ih().keyDownEvent()) {
			if (ih().isKeyDown(SDLK_s) && sdlutils().currRealTime() - lastCreatedTime > time_) {
				lastCreatedTime = sdlutils().currRealTime();
				Vector2D p = tr_->getPos();
				Vector2D v = tr_->getDir();
				int w = tr_->getW();
				int h = tr_->getH();
				int r = tr_->getRotation();

				p = p + Vector2D(w / 2, h / 2) - Vector2D(0.0f, h / 2.0f + 5.0f + 12.0f).rotate(r) - Vector2D(2.0f, 10.0f);
				v = Vector2D(0.0f, -1.0f).rotate(r) * (v.magnitude() + 5.0f);

				msg::Message m;
				m.id = msg::BULLET_SHOOT;
				m.bullet.p = p;
				m.bullet.v = v;
				m.bullet.h = w;
				m.bullet.w = w;
				m.bullet.r = r;

				manager_->send(m);


			}
		}
	}
}

void FighterGunSystem::receive(const msg::Message& m)
{
	switch (m.id)
	{
	case msg::START_GAME:
		active = true;
		break;
	case msg::ROUNDOVER:
	case msg::GAMEOVER:
		active = false;
		break;
	default:
		break;
	}
}
