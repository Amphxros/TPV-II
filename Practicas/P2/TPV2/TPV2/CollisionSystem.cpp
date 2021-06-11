#include "CollisionSystem.h"

#include "Transform.h"
#include "ecs/Manager.h"
#include "sdlutils/SDLUtils.h"
#include "utils/Collisions.h"
#include "messages.h"

CollisionSystem::CollisionSystem():active_(false)
{
}

CollisionSystem::~CollisionSystem()
{
}
void CollisionSystem::update()
{
	if(!active_){
		return;
	}
	auto entities = manager_->getEnteties();
	for(Entity* a:entities){
		if(a->hasGroup<Asteroid>()){
			for(Entity* b:entities){
				if(b->hasGroup<Bullet>()){
					//se comprueba col aqui
					if (collides(a->getComponent<Transform>(),
						b->getComponent<Transform>())) {
						Message n;
						n.type_ = _COLLISION_ASTEROID_BULLET;
						n.entity_.entityA = a;
						n.entity_.entityB = b;
						manager_->send(n);

					}
				}
			}
		}
	}
}

void CollisionSystem::receive(const Message& m)
{
	switch(m.type_){
	case _ROUND_START_:
		active_ = true;
		break;
	case _ROUND_OVER_:
		active_ = false;
		break;
	case _GAME_START_:
		active_ = true;
		break;
	case _GAME_OVER_:
		active_ = false;
		break;

	}
}

bool CollisionSystem::collides(Transform* tr1, Transform* tr2)
{
	return Collisions::collides( //
			tr1->pos_, tr1->width_, tr1->height_, //
			tr2->pos_, tr2->width_, tr2->height_);
	
}
