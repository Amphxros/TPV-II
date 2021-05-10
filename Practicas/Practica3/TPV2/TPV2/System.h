#pragma once
#include "Component.h"
class Manager;
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
	void setManager(Manager* m);
protected:
	Manager* mngr;
	ecs::SystemID id_;
};


enum GameState {NEW,RUNNING,PAUSED,GAMEOVER};
class GameCtrlSystem : public System {
public:
	GameCtrlSystem();

	virtual ~GameCtrlSystem();
	// - a este método se le va a llamar cuando muere el caza.
	// - desactivar los asteroides y las balas, actualizar el estado del juego, etc.
	void onFighterDeath();
	// - a este método se le va a llamar cuando no haya más asteroides.
	// - desactivar todas las balas, etc.
	void onAsteroidsExtinction();
	// - devuelve el estado del juego.
	GameState getGameState() { return gs; };
	// - inicializar el estado del juego si es necesario, etc.
	virtual void init() override;
	// - si el juego está parado y el jugador pulsa SDLK_SPACE cambia el estado como
	// en la práctica 1, etc.
	virtual void update() override;
private:
	GameState gs;

	//texturas 
	Texture* msgInit; 
	Texture* msgPause;
	Texture* msgGameOver;
};



class FighterSystem : public System {
public:
	FighterSystem();
	virtual ~FighterSystem();
	// - poner el caza en el centro con velocidad 0 y rotación 0. No hace falta
	// desactivar la entidad (no dibujarla si el juego está parado en RenderSystem).
	// - avisar al GameCtrlSystem que se ha muerto el caza (se puede también avisar
	// directamente en el CollisionSystem)
	void onCollisionWithAsteroid(Entity* a);
	// - crear la entidad del caza, añadir sus componentes (Transform, Health, etc.)
	// y asociarla con el handler correspondiente.
	void init() override;
	// - si el juego está parado no hacer nada.
	// - actualizar la velocidad del caza y moverlo como en la práctica 1.
	void update() override;
private:
	GameCtrlSystem* gameSys;
	Entity* fighter;
};



class AsteroidsSystem : public System {

public:
	AsteroidsSystem(int numAsteroid, double width, double height);
	virtual ~AsteroidsSystem();

	virtual void init() override;
	virtual void update() override;
	void OnCollision(Entity* A);
private:

	void createAsteroid();
	GameCtrlSystem* gameSys;
	int numAsteroids;
	int nAsteroids; //current num of asteroids
	double width_;
	double height_;

	std::size_t time_, lastTime_;

};


class BulletsSystem : public System {

public:
	BulletsSystem();
	virtual ~BulletsSystem();

	virtual void init() override;
	virtual void update() override;
	
	// - añadir una bala al juego, como en la práctica 1. La rotación de la bala
	// sería vel.angle(Vector2D(0.0f,-1.0f))
	void shoot(Vector2D pos, Vector2D vel, double width, double height);
	void onCollisionWithAsteroid(Entity* b, Entity* a);

private:
	GameCtrlSystem* gameSys;
};


class CollisionSystem : public System {
public:
	CollisionSystem();
	virtual void init() override;
	virtual void update() override;
private:
	FighterSystem* fighterSys;
	BulletsSystem* bulletSys;
	AsteroidsSystem* astSys;
	GameCtrlSystem* gameSys;

	bool isOnCollision(Transform* tA, Transform* tB);

};



class FighterGunSystem : public System {
public:
	FighterGunSystem();
	virtual ~FighterGunSystem();
		virtual void init() override;
	// - si el juego está parado no hacer nada. Si el jugador pulsa SDLK_S, llamar
	// a shoot del BulletsSystem para añadir una bala al juego, etc.
	// - se puede incluir ese comportamiento en el FighterSystem directamente en
	// lugar de definirlo en un sistema separado
	virtual void update() override;
private:
	BulletsSystem* bulletSys;
	GameCtrlSystem* gameSys;

	std::size_t time_, lastTime_;

};



class RenderSystem : public System {
public:
	RenderSystem();
	virtual void init() override;
	virtual void update() override;
};