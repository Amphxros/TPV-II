#include "GameCtrlSystem.h"
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
	m.info.gameWin = true;
	manager_->send(m);
}

