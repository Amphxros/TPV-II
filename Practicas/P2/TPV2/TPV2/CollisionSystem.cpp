#include "CollisionSystem.h"
#include "ecs/Manager.h"
CollisionSystem::CollisionSystem():active_(false)
{
}

CollisionSystem::~CollisionSystem()
{
}
void CollisionSystem::update()
{
	if(!active){
		return;
	}
	auto entities = manager_->getEnteties();
	for(Entity* a:entities){
		if(manager_->hasGroup<Asteroid>(a)){
			for(Entity* b:entities){
				if(manager_->hasGroup<Bullet>(b)){
					//se comprueba col aqui
			
				}
			}
		}
	}
}

void CollisionSystem::receive(const Message& m)
{
	switch(m.type){
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
