// This file is part of the course TPV2@UCM - Samir Genaim

#include "GhostsSystem.h"

#include "../components/Image.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"

#include <cassert>
#include <cstdlib>
#include <algorithm>

GhostsSystem::GhostsSystem() :
		active_(false), //
		currNumOfGhosts_(0), //
		maxNumOfGhosts_(10), //
		lastTimeCreatedGhosts_(0), //
		ghostCreationFrequency_(5000), //
		sprites_(nullptr), //
		pacmanTR_(nullptr) {
}

GhostsSystem::~GhostsSystem() {
}

void GhostsSystem::init() {
	Entity *pacman = manager_->getHandler<PacMan>();
	assert(pacman != nullptr);

	pacmanTR_ = manager_->getComponent<Transform>(pacman);
	assert(pacmanTR_ != nullptr);

	sprites_ = &sdlutils().images().at("pacman_sprites");
}

void GhostsSystem::receive(const Message &m) {
	switch (m.type_) {
	case _ROUND_START_: {
		active_ = true;
		lastTimeCreatedGhosts_ = sdlutils().currRealTime();
		break;
	}
	case _ROUND_OVER_: {
		removeAllGhosts();
		active_ = false;
		break;
	}
	default:
		break;

	}
}

void GhostsSystem::update() {

	if (!active_)
		return;

	if (currNumOfGhosts_ < maxNumOfGhosts_
			&& sdlutils().currRealTime()
					> lastTimeCreatedGhosts_ + ghostCreationFrequency_) {
		lastTimeCreatedGhosts_ = sdlutils().currRealTime();
		addGhost();
	}

	auto &r = sdlutils().rand();

	for (auto &e : manager_->getEnteties()) {
		if (manager_->hasGroup<Ghosts>(e)) {
			auto tr = manager_->getComponent<Transform>(e);

			// con probabilidad del 0.5% cambiamos el vector de velocidad
			// para seguir al pacman
			if (r.nextInt(0, 1000) < 5) {
				Vector2D vecTowardsPacman =
						(pacmanTR_->pos_ - tr->pos_).normalize();

				tr->vel_ = vecTowardsPacman * 0.5f;
			}

			// cambiar la posición del fantasma
			tr->pos_ = tr->pos_ + tr->vel_;

			// evitar que el fantasma salga por la derecha/izquierdo
			if (tr->pos_.getX() < 0) {
				tr->pos_.setX(0);
				tr->vel_.setX(-tr->vel_.getX());
			} else if (tr->pos_.getX() > sdlutils().width() - tr->width_) {
				tr->pos_.setX(sdlutils().width() - tr->width_);
				tr->vel_.setX(-tr->vel_.getX());
			}

			// evitar que el fantasma salga por arriba/abajo
			if (tr->pos_.getY() < 0) {
				tr->pos_.setY(0);
				tr->vel_.setY(-tr->vel_.getY());
			} else if (tr->pos_.getY() > sdlutils().height() - tr->height_) {
				tr->pos_.setY(sdlutils().height() - tr->height_);
				tr->vel_.setY(-tr->vel_.getY());
			}

		}

	}

}

void GhostsSystem::addGhost() {

	constexpr int dim = 30;
	auto &r = sdlutils().rand();

	// crear la entidad y añadirla al grupo Ghosts
	auto e = manager_->addEntity();
	manager_->setGroup<Ghosts>(e, true);

	// numeros aleatorios para elegir de que esquina sale el fantasma
	auto rX = r.nextInt(0, 2);
	auto rY = r.nextInt(0, 2);

	// las posición inicial del fantasma en función de los numeros aleatorios
	auto x = rX * (sdlutils().width() - dim);
	auto y = rY * (sdlutils().width() - dim);
	Vector2D pos(x, y);

	// la velocidad inicial es vertical, depend de que esquina sale
	Vector2D vel(0.0f, (rY == 0 ? 0.5f : -0.5f));

	// añadir el Transfrom
	manager_->addComponent<Transform>(e, pos, vel, dim, dim, 0.0f);

	// añadir la imagen
	manager_->addComponent<Image>( //
			e, // entity
			sprites_, // texture
			8, 8, // rows
			5, 5, 115, 115, // x,y,w,h
			4, 0, 1, 8 // srow,scol,nrows,ncols
			);

	// incrementar el número de fantasmas
	currNumOfGhosts_++;
}

void GhostsSystem::removeAllGhosts() {

	// disactivar todos los fantasmas
	for (auto &e : manager_->getEnteties()) {
		if (manager_->hasGroup<Ghosts>(e)) {
			manager_->setActive(e, false);
		}
	}

	//  el número de fantasmas es 0
	currNumOfGhosts_ = 0;
}
