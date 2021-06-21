#include "Follow.h"
#include "Transform.h"


Follow::Follow(Transform* tr, Transform* target):
	tr_(tr), target_(target)
{
}

Follow::~Follow()
{
}

void Follow::update()
{
	tr_->setDir(tr_->getDir().rotate(tr_->getDir().angle(target_->getPos() - tr_->getPos()) > 0 ? 1.0f : -1.0f));
}
