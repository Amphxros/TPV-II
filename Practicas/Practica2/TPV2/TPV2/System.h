#pragma once
#include "Component.h"
class System
{
public:
	System();
	System(ecs::SystemID id);

	virtual ~System() {};
	virtual void init() {};
	virtual void update() {};
	inline ecs::SystemID getID() { return id_; }
	inline Manager* getMngr() { return mngr; }
	inline void setManager(Manager* m) { mngr = m; }
protected:
	Manager* mngr;
	ecs::SystemID id_;
};

class GameCtrlSystem : public System {
public:
	GameCtrlSystem();

	virtual ~GameCtrlSystem();
	// - a este m�todo se le va a llamar cuando muere el caza.
	// - desactivar los asteroides y las balas, actualizar el estado del juego, etc.
	void onFighterDeath();
	// - a este m�todo se le va a llamar cuando no haya m�s asteroides.
	// - desactivar todas las balas, etc.
	void onAsteroidsExtinction();
	// - devuelve el estado del juego.
	State getGameState();
	// - inicializar el estado del juego si es necesario, etc.
	virtual void init() override;
	// - si el juego est� parado y el jugador pulsa SDLK_SPACE cambia el estado como
	// en la pr�ctica 1, etc.
	virtual void update() override;
};

class AsteroidsSystem : public System {

public:
	AsteroidsSystem(int numAsteroid);
	virtual ~AsteroidsSystem();

	virtual void init() override;
	virtual void update() override;
private:
	Texture* asteroidA;
	Texture* asteroidB;
	int numAsteroids;
	int nAsteroids; //current num of asteroids
	std::size_t time_;
};
class BulletsSystem : public System {

public:
	BulletsSystem();
	virtual void init() override;
	virtual void update() override;
};
class CollisionSystem : public System {
public:
	CollisionSystem();
	virtual void init() override;
	virtual void update() override;
};
class RenderSystem : public System {
public:
	RenderSystem();
	virtual void init() override;
	virtual void update() override;
};