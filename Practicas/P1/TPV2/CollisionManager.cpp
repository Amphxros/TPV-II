#include "CollisionManager.h"
#include "ecs/Entity.h"
#include "ecs/Manager.h"
#include"Health.h"

CollisionManager::CollisionManager()	:	Component()
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::init()
{
	astManager = entity_->getComponent<AsteroidsManager>();
	mState = entity_->getComponent<State>();

}

void CollisionManager::update()
{
	auto entities = entity_->getMngr()->getEnteties();

	for (auto& ast : entities) {
		if (ast->hasGroup<Asteroids>()) {
			Transform* a = ast->getComponent<Transform>();

			//comprobamos colisiones con las balas
			for (auto& bul : entities) {
				if (bul->hasGroup<Bullets>()) {
					Transform* b = bul->getComponent<Transform>();
					assert(a != nullptr && b != nullptr);
					
						if (collides(a, b)) {
						astManager->onCollisionWithBullet(ast);
						bul->setActive(false);
						if(astManager->noMoreAsteroids()){
							mState->changeState(GameState::GAMEOVER, true);
						}

					}
				}

			}

			// Colisiones con Fighter
			Transform* tr_Fighter = entity_->getMngr()->getHandler<Fighter>()->getComponent<Transform>();
			assert(tr_Fighter!=nullptr);
	
		if (collides(a, tr_Fighter)) {
				//quitar vida y comprobar si su vida es 0 -> cambiar a gameOver : cambiar a pausa
				Health* h = entity_->getMngr()->getHandler<Fighter>()->getComponent<Health>();
				h->setHealth(h->getHealth() - 1);
				if(h->getHealth()>0){
					mState->changeState(GameState::PAUSE);
				}
				else{
					
					mState->changeState(GameState::GAMEOVER);
				}

			}

		}
	}

}

bool CollisionManager::collides(Transform* a, Transform* b) {

	return (Collisions::collidesWithRotation(a->getPos(), a->getW(), a->getH(), a->getRotation(), 
												b->getPos(), b->getW(), b->getH(), b->getRotation()));
}
