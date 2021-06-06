#include "GameCtrlSystem.h"

#include "messages.h"
GameCtrlSystem::GameCtrlSystem()
{
}

GameCtrlSystem::~GameCtrlSystem()
{
}

void GameCtrlSystem::onFighterDeath()
{
	
}

void GameCtrlSystem::onAsteroidsExtinction()
{	
	Message m;
	m.type_ = _GAME_OVER_;
	std::cout << "Game over";

	manager_->send(m);
}

void GameCtrlSystem::init()
{
}

void GameCtrlSystem::update()
{
}

void GameCtrlSystem::receive(const Message& m)
{
	switch(m.type_){

	}
}
