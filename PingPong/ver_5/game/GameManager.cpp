// This file is part of the course TPV2@UCM - Samir Genaim

#include "GameManager.h"

#include <cassert>
#include <string>

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Collisions.h"

GameManager::GameManager(GameObject *b, GameObject *left, GameObject *right) :
		score_(), //
		state_(NEWGAME), //
		maxScore_(5), //
		ball_(b), //
		leftPaddle_(left), //
		rightPaddle_(right) {
}

GameManager::~GameManager() {
}

