// This file is part of the course TPV2@UCM - Samir Genaim

#include "PacManSystem.h"

#include "../components/Image.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"

#include <SDL.h>

PacManSystem::PacManSystem() :
		active_(false), //
		sprites_(nullptr), //
		pacmanTR_(nullptr) {
}

PacManSystem::~PacManSystem() {
}

void PacManSystem::init() {

	sprites_ = &sdlutils().images().at("pacman_sprites");
	assert(sprites_ != nullptr);

	// crear la entidad del pacman
	Entity *e = manager_->addEntity();
	manager_->setHandler<PacMan>(e);

	// añadir el transform y resetearlo
	pacmanTR_ = manager_->addComponent<Transform>(e);
	resetPacMan();

	// añadir la imagen
	manager_->addComponent<Image>( //
			e, // entity
			&sdlutils().images().at("pacman_sprites"), // texture
			8, 8, // rows
			5, 5, 115, 115, // x,y,w,h
			0, 0, 1, 2, // srow,scol,nrows,ncols
			100 // duration
			);

}

void PacManSystem::receive(const Message &m) {
	switch (m.type_) {
	case _ROUND_START_: {
		active_ = true;
		break;
	}
	case _ROUND_OVER_: {
		resetPacMan();
		active_ = false;
		break;
	}
	default:
		break;

	}
}

void PacManSystem::update() {

	if (!active_)
		return;

	// move el pacman con las flechas:
	// LEFT,RIGHT giran 90 grados hacía la izquierda/derecha
	// UP empieza a move en la dirección al que mira actualmente
	// DOWN: poner la velocidad a 0 (parar)
	//
	if (ih().keyDownEvent()) {
		if (ih().isKeyDown(SDL_SCANCODE_RIGHT)) {
			pacmanTR_->rotation_ = fmod(pacmanTR_->rotation_ + 90.0f, 360.0f);
			pacmanTR_->vel_ = pacmanTR_->vel_.rotate(90.0f);
		} else if (ih().isKeyDown(SDL_SCANCODE_LEFT)) {
			pacmanTR_->rotation_ = fmod(pacmanTR_->rotation_ - 90.0f, 360.0f);
			pacmanTR_->vel_ = pacmanTR_->vel_.rotate(-90.0f);
		} else if (ih().isKeyDown(SDL_SCANCODE_UP)) {
			pacmanTR_->vel_ = Vector2D(0.0f, -2.0f).rotate(
					pacmanTR_->rotation_);
		} else if (ih().isKeyDown(SDL_SCANCODE_DOWN)) {
			pacmanTR_->vel_ = Vector2D(0.0f, 0.0f);
		}
	}

	// mover el pacman
	pacmanTR_->pos_ = pacmanTR_->pos_ + pacmanTR_->vel_;

	// comprobar si choca con la parte izqierda/derecha de la ventana
	if (pacmanTR_->pos_.getX() < 0) {
		pacmanTR_->pos_.setX(0);
		pacmanTR_->vel_ = Vector2D(0.0f, 0.0f);
	} else if (pacmanTR_->pos_.getX()
			> sdlutils().width() - pacmanTR_->width_) {
		pacmanTR_->pos_.setX(sdlutils().width() - pacmanTR_->width_);
		pacmanTR_->vel_ = Vector2D(0.0f, 0.0f);
	}

	// comprobar si choca con la parte de arriba/aboja de la ventana
	if (pacmanTR_->pos_.getY() < 0) {
		pacmanTR_->pos_.setY(0);
		pacmanTR_->vel_ = Vector2D(0.0f, 0.0f);
	} else if (pacmanTR_->pos_.getY()
			> sdlutils().height() - pacmanTR_->height_) {
		pacmanTR_->pos_.setY(sdlutils().height() - pacmanTR_->height_);
		pacmanTR_->vel_ = Vector2D(0.0f, 0.0f);
	}

}

void PacManSystem::resetPacMan() {
	// poner el pacman en el centro
	constexpr int dim = 40;
	pacmanTR_->width_ = dim;
	pacmanTR_->height_ = dim;
	pacmanTR_->rotation_ = 0;
	pacmanTR_->pos_ = Vector2D((sdlutils().width() - dim) / 2,
			(sdlutils().height() - dim) / 2);
	pacmanTR_->vel_ = Vector2D(0.0f, 0.0f);
}
