// This file is part of the course TPV2@UCM - Samir Genaim

#include "GameManagerSystem.h"

#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "messages.h"

GameManagerSystem::GameManagerSystem() :
		state_(NEWGAME), //
		remainingRounds_(0), //
		maxRounds_(3) {
}

GameManagerSystem::~GameManagerSystem() {
}

void GameManagerSystem::init() {
	remainingRounds_ = maxRounds_;
	chageState(NEWGAME, _GAME_START_);
}

void GameManagerSystem::update() {
	if (state_ != RUNNING) {
		if (ih().isKeyDown(SDL_SCANCODE_SPACE)) {
			switch (state_) {
			case NEWGAME:
				chageState(RUNNING, _ROUND_START_);
				break;
			case PAUSED:
				chageState(RUNNING, _ROUND_START_);
				break;
			case GAMEOVER:
				remainingRounds_ = maxRounds_;
				chageState(NEWGAME, _GAME_START_);
				break;
			default:
				break;
			}
		}
	}
}

void GameManagerSystem::receive(const Message &msg) {
	switch (msg.type_) {
	case _PACMAN_COLLIDES_WITH_FOOD_:
		break;
	case _PACMAN_COLLIDES_WITH_GHOST_:
		handlePacMancolliedsWithGhost(msg);
		break;
	case _NO_MORE_FRUIT_:
		handleNoMoreFruit(msg);
		break;
	default:
		break;
	}
}

void GameManagerSystem::handlePacMancolliedsWithGhost(const Message &msg) {

	// al chocar con 2 fantasmas, en ese caso no queremos contar el segundo
	if (state_ != RUNNING)
		return;

	remainingRounds_--;
	chageState(PAUSED, _ROUND_OVER_);

	if (remainingRounds_ == 0) {
		chageState(GAMEOVER, _GAME_OVER_, false);
	}
}

void GameManagerSystem::handleNoMoreFruit(const Message &msg) {
	chageState(PAUSED, _ROUND_OVER_, true);
	chageState(GAMEOVER, _GAME_OVER_, true);
}

void GameManagerSystem::chageState(GameSate state, Uint8 msgType, bool won) {

	// change the state
	state_ = state;

	// send a message
	Message m;
	m.type_ = static_cast<MsgType>(msgType);
	m.round_.remainingRounds_ = remainingRounds_;
	m.round_.pacmanWon_ = won;
	manager_->send(m);
}
