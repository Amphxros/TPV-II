#pragma once

#include "ecs/System.h"

class GameCtrlSystem : public System
{
public:
	enum GameState{ NEW, RUNNING, PAUSE, GAMEOVER };

	GameCtrlSystem();
	virtual ~GameCtrlSystem();

	// - a este m�todo se le va a llamar cuando muere el caza.
	// - desactivar los asteroides y las balas, actualizar el estado del juego, etc.
	void onFighterDeath();
	// - a este m�todo se le va a llamar cuando no haya m�s asteroides.
	// - desactivar todas las balas, etc.
	void onAsteroidsExtinction();

	inline GameState getGameState() { return gameState; }
	// - inicializar el estado del juego si es necesario, etc.
	void init() override;
	// - si el juego est� parado y el jugador pulsa SDLK_SPACE cambia el estado como
	// en la pr�ctica 1, etc.
	void update() override;

	void receive(const Message& m) override;

private:
	GameState gameState;

};