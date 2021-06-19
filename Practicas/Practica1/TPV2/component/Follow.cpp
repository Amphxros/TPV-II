#include "Follow.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
Follow::Follow(): Component(), tr_(nullptr), target_(nullptr)
{
}

Follow::~Follow()
{
}

void Follow::init()
{
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
	auto player = entity_->getMngr()->getHandler<Fighter>();
	target_ = player->getComponent<Transform>();
	assert(target_ != nullptr);

}

void Follow::update()
{
	auto dir = tr_->getDir();
	auto p = tr_->getPos();

	dir.set(dir.rotate(dir.angle(target_->getPos() - p) > 0 ? 1.0f : -1.0f));

	tr_->setDir(dir);
}
