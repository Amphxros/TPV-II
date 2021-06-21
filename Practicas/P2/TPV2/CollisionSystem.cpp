#include "CollisionSystem.h"
#include "utils/Collisions.h"
#include "component/Transform.h"
#include "ecs/Manager.h"
#include "Message.h"
CollisionSystem::CollisionSystem()
{
}

void CollisionSystem::init()
{
}

void CollisionSystem::update()
{
	auto entities = manager_->getEnteties();
	Entity* fighter = manager_->getHandler<Fighter>();
	Transform* trFighter = manager_->getComponent<Transform>(fighter);

	for (auto ast : entities) {
		if (manager_->hasGroup<Asteroids>(ast)) {
			Transform* trA = manager_->getComponent<Transform>(ast);
			for (auto bul : entities) {
				if (manager_->hasGroup<Bullets>(bul)) {
					Transform* trB = manager_->getComponent<Transform>(bul);

					if (collides(trA, trB)) {
						msg::Message m_;
						m_.id = msg::COLLISIONBULLET;
						manager_->send(m_);
					}

				}
			}


			if (collides(trA, trFighter)) {
				msg::Message m;
				m.id = msg::COLLISIONFIGHTER;
				manager_->send(m);
			}

		}
	}
}

void CollisionSystem::receive(const msg::Message& m)
{
}

bool CollisionSystem::collides(Transform* a, Transform* b)
{
	return (Collisions::collidesWithRotation(a->getPos(), a->getW(), a->getH(), a->getRotation(),
											b->getPos(), b->getW(), b->getH(), b->getRotation()));
}
