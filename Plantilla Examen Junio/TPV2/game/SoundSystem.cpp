// This file is part of the course TPV2@UCM - Samir Genaim

#include "SoundSystem.h"

#include "../sdlutils/SDLUtils.h"
#include "messages.h"

SoundSystem::SoundSystem() :
		chompSound_(nullptr), //
		deathSound_(nullptr), //
		eatSound_(nullptr), //
		introSound_(nullptr), //
		wonSound_(nullptr) {
}

SoundSystem::~SoundSystem() {
}

void SoundSystem::init() {
	chompSound_ = &sdlutils().soundEffects().at("pacman_chomp");
	deathSound_ = &sdlutils().soundEffects().at("pacman_death");
	eatSound_ = &sdlutils().soundEffects().at("pacman_eat");
	introSound_ = &sdlutils().soundEffects().at("pacman_intro");
	wonSound_ = &sdlutils().soundEffects().at("pacman_won");
}

void SoundSystem::receive(const Message &msg) {
	switch (msg.type_) {
	case _GAME_START_: {
		introSound_->play(2, 0); // reproducir el sonido 3 veces en el canal 0
		break;
	}
	case _GAME_OVER_: {
		if (msg.round_.pacmanWon_)
			wonSound_->play(0, 0);   // reproducir el sonido 1 vez en el canal 0
		break;
	}
	case _ROUND_START_: {
		SoundEffect::haltChannel(0); // parar el sonido del canal 0
		// chompSound_->play(-1, 0); // reproducir en bucle (hasta que acabe la ronda)
		break;
	}
	case _ROUND_OVER_: {
		SoundEffect::haltChannel(0); // parar el sonido del canal 0
		if (!msg.round_.pacmanWon_)
			deathSound_->play(0, 0); // reproducir el sonido 1 vez en el canal 0
		break;
	}
	case _PACMAN_COLLIDES_WITH_FOOD_: {
		eatSound_->play(0, 1); // reproducir el sonido 1 vez en el canal 0
		break;
	}
	default:
		break;
	}
}

void SoundSystem::update() {
}
