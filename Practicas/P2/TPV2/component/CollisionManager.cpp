//#include "CollisionManager.h"
//#include "../ecs/Entity.h"
//#include "../ecs/Manager.h"
//#include "GameCtrl.h"
//#include "../sdlutils/SDLUtils.h"
//#include "Health.h"
//
//CollisionManager::CollisionManager() :
//	Component(), astManager(nullptr), mState(nullptr)
//{
//}
//
//CollisionManager::~CollisionManager()
//{
//}
//
//void CollisionManager::init()
//{
//	astManager = entity_->getComponent<AsteroidsManager>();
//	mState = entity_->getComponent<State>();
//
//}
//
//void CollisionManager::update()
//{
//	auto entities = entity_->getMngr()->getEnteties();
//
//	for (auto& ast : entities) {
//		if (ast->hasGroup<Asteroids>()) {
//			Transform* a = ast->getComponent<Transform>();
//
//			//comprobamos colisiones con las balas
//			for (auto& bul : entities) {
//				if (bul->hasGroup<Bullets>()) {
//					Transform* b = bul->getComponent<Transform>();
//					assert(a != nullptr && b != nullptr);
//					
//						if (collides(a, b)) {
//						astManager->onCollisionWithBullet(ast);
//						bul->setActive(false);
//						if(astManager->noMoreAsteroids()){
//							mState->changeState(GameState::GAMEOVER, true);
//						}
//
//						sdlutils().soundEffects().at("explosion").play(0, 1);
//
//					}
//				}
//			}
//
//			// Colisiones con Fighter
//			Transform* tr_Fighter = entity_->getMngr()->getHandler<Fighter>()->getComponent<Transform>();
//			assert(tr_Fighter!=nullptr);
//	
//		if (collides(a, tr_Fighter)) {
//				//quitar vida y comprobar si su vida es 0 -> cambiar a gameOver : cambiar a pausa
//				onFighterCollision();
//				astManager->endGame();
//
//			}
//
//		}
//	}
//
//}
//
//void CollisionManager::onFighterCollision()
//{
//	Transform* tr_Fighter = entity_->getMngr()->getHandler<Fighter>()->getComponent<Transform>();
//	Health* h = entity_->getMngr()->getHandler<Fighter>()->getComponent<Health>();
//	h->setHealth(h->getHealth() - 1);
//
//	if (h->getHealth() > 0) {
//		sdlutils().musics().at("imperial_march").pauseMusic();
//		mState->changeState(GameState::PAUSE);
//	}
//	else {
//		sdlutils().musics().at("imperial_march").haltMusic();
//		mState->changeState(GameState::GAMEOVER);
//		h->resetHealth();
//	}
//
//	tr_Fighter->setPos(Vector2D(sdlutils().width() / 2 - 25, sdlutils().height() / 2 - 25));
//	tr_Fighter->setDir(Vector2D());
//	tr_Fighter->setRotation(0.0f);
//
//
//	auto& entities = entity_->getMngr()->getEnteties();
//
//	for (auto e : entities) {
//		if (e->hasGroup<Asteroids>() || e->hasGroup<Bullets>()) {
//			e->setActive(false);
//		}
//	}
//}
//
//bool CollisionManager::collides(Transform* a, Transform* b) {
//
//	return (Collisions::collidesWithRotation(a->getPos(), a->getW(), a->getH(), a->getRotation(), 
//												b->getPos(), b->getW(), b->getH(), b->getRotation()));
//}
