// This file is part of the course TPV2@UCM - Samir Genaim

#include "CollisionSystem.h"

#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Collisions.h"
#include "messages.h"

#include <cassert>


CollisionSystem::CollisionSystem() :
		active_(false), //
		pacmanTr_(nullptr) {
}

CollisionSystem::~CollisionSystem() {
}

void CollisionSystem::receive(const Message &m) {
	switch (m.type_) {
	case _ROUND_START_:
		active_ = true;
		break;
	case _ROUND_OVER_:
		active_ = false;
		break;
	default:
		break;
	}
}

void CollisionSystem::init() {
	Entity *pacman = manager_->getHandler<PacMan>();
	assert(pacman != nullptr);
	pacmanTr_ = manager_->getComponent<Transform>(pacman);
	assert(pacmanTr_ != nullptr);
}

void CollisionSystem::update() {

	if (!active_)
		return;

	auto &entities_ = manager_->getEnteties();
	auto size = entities_.size();

	for (auto i = 0u; i < size; i++) {

		Entity *e = entities_[i];

		if (!manager_->isActive(e))
			continue;

		if (manager_->hasGroup<Food>(e)) {
			if (collieds(pacmanTr_, manager_->getComponent<Transform>(e))) {
				Message m;
				m.type_ = _PACMAN_COLLIDES_WITH_FOOD_;
				m.food_.entity_ = e;
				manager_->send(m);
			}
		} else if (manager_->hasGroup<Ghosts>(e)) {
			if (collieds(pacmanTr_, manager_->getComponent<Transform>(e))) {
				Message m;
				m.type_ = _PACMAN_COLLIDES_WITH_GHOST_;
				m.ghost_.entity_ = e;
				manager_->send(m);
			}
		}

	}

}

bool CollisionSystem::collieds(Transform *tr1, Transform *tr2) {
	return Collisions::collides( //
			tr1->pos_, tr1->width_, tr1->height_, //
			tr2->pos_, tr2->width_, tr2->height_);
}
