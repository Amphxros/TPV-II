#include "GameCtrlSystem.h"

#include "sdlutils/SDLUtils.h"
#include "sdlutils/InputHandler.h"
#include "ecs/Manager.h"

GameCtrlSystem::GameCtrlSystem(): System(), mGameState_(GameState::NEW)
{
}

GameCtrlSystem::~GameCtrlSystem()
{
}

void GameCtrlSystem::init()
{
	mGameState_ = GameState::NEW;

}

void GameCtrlSystem::update()
{
	if (ih().keyDownEvent()) {
		if (ih().isKeyDown(SDL_SCANCODE_SPACE) && mGameState_ != GameState::RUNNING) {
			msg::Message m;
			if (mGameState_ == GameState::GAMEOVER) {
				mGameState_ = GameState::NEW;
				m.id = msg::INIT_GAME;
				m.info.currState = (int)(mGameState_);
				manager_->send(m);
			}
			else {
				m.id = msg::START_GAME;
				
				mGameState_ = GameState::RUNNING;
				m.num.n = 10;
				manager_->send(m);
			}
		}
	}
}

void GameCtrlSystem::receive(const msg::Message& m)
{
	switch (m.id)
	{
		
	case msg::COLLISIONFIGHTER:
		onFighterDeath();
		break;
	case msg::ROUNDOVER:
		mGameState_ = GameState::PAUSED;
		break;
	case msg::GAMEOVER:
		mGameState_ = GameState::GAMEOVER;
		break;

	default:
		break;
	}
}

void GameCtrlSystem::onFighterDeath()
{
	
}

void GameCtrlSystem::onAsteroidsExtinction()
{
	msg::Message m;
	m.id = msg::GAMEOVER;
	m.info.hasWon = true;
	manager_->send(m);
}

