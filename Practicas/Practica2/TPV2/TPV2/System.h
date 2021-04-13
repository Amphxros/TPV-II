#pragma once
#include "Component.h"
class System
{
public:
	System();
	virtual ~System() {};
	virtual void init() {};
	virtual void update() {};
protected:
	Manager* mngr;
};

class GameCtrlSystem : public System {
public:
	// - a este método se le va a llamar cuando muere el caza.
	// - desactivar los asteroides y las balas, actualizar el estado del juego, etc.
	void onFighterDeath();
	// - a este método se le va a llamar cuando no haya más asteroides.
	// - desactivar todas las balas, etc.
	void onAsteroidsExtinction();
	// - devuelve el estado del juego.
	State getGameState();
	// - inicializar el estado del juego si es necesario, etc.
	virtual void init() override;
	// - si el juego está parado y el jugador pulsa SDLK_SPACE cambia el estado como
	// en la práctica 1, etc.
	virtual void update() override;
};

class AsteroidsSystem : public System {

public:
	AsteroidsSystem();
	virtual ~AsteroidsSystem();
private:
	Texture* asteroidA;
	Texture* asteroidB;
	int numAsteroids;
	int nAsteroids; //current num of asteroids
	std::size_t time_;
};
class BulletsSystem : public System {

};
class CollisionSystem : public System {

};
