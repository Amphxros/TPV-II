// This file is part of the course TPV2@UCM - Samir Genaim

#include "FoodSystem.h"

#include "../components/Image.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Vector2D.h"

FoodSystem::FoodSystem() :
		numOfFoodPieces_(0) {
}

FoodSystem::~FoodSystem() {
}

void FoodSystem::init() {
}

void FoodSystem::receive(const Message &m) {

	switch (m.type_) {
	case _GAME_START_: {
		initFood();
		break;
	}
	case _PACMAN_COLLIDES_WITH_FOOD_: {
		handlePacManCollidesWithFood(m);
		break;
	}
	default:
		break;

	}

}

void FoodSystem::update() {
	// el update no hace nada en esta vesión
}

void FoodSystem::initFood() {

	// dividir la pantalla en celdas de tamano 100x100, y poner una cereza
	// en el centro de cada celda
	constexpr int dim = 25;
	constexpr int cell_dim = 100;
	constexpr int pad = (cell_dim - dim) / 2;

	auto cols = (sdlutils().width()) / cell_dim;
	auto rows = (sdlutils().height()) / cell_dim;

	for (int r = 0; r < rows; r += 1) {
		for (int c = 0; c < cols; c += 1) {

			// crear una entidad y añadirla al grupo
			Entity *e = manager_->addEntity();
			manager_->setGroup<Food>(e, true);

			// añadir el transform (coloca la fruta en el centro de la celda)
			auto tr = manager_->addComponent<Transform>(e);
			tr->width_ = dim;
			tr->height_ = dim;
			tr->pos_ = Vector2D(pad + cell_dim * c, pad + cell_dim * r);

			// añadir la imagin de cereza
			manager_->addComponent<Image>( //
					e, // entity
					&sdlutils().images().at("pacman_sprites"), // texture
					8, 8, // rows
					5, 5, 115, 115, // x,y,w,h
					1, 4, 1, 1 // srow,scol,nrows,ncols
					);

			// incrementar el número de frutas
			numOfFoodPieces_++;
		}
	}
}

void FoodSystem::handlePacManCollidesWithFood(const Message &m) {

	// cuando el pacman choca con una fruta la desactivamos
	manager_->setActive(m.food_.entity_, false);
	numOfFoodPieces_--;

	// si no queda más fruta enviamos un mensaje
	if (numOfFoodPieces_ == 0) {
		Message m;
		m.type_ = _NO_MORE_FRUIT_;
		manager_->send(m);
	}

}

void FoodSystem::removeAllFood() {
}
