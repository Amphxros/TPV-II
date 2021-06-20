#pragma once

#include "ecs/System.h"
#include "Message.h"

enum GameState{ NEW, RUNNING, PAUSED, GAMEOVER};

class GameCtrlSystem :	public System	{

public:

	GameCtrlSystem();
	virtual ~GameCtrlSystem();

	virtual void init() override;
	virtual void update() override;
	void receive(const msg::Message& m) override;
	GameState getGameState() { return mGameState_; };

private:

	GameState mGameState_;
	// - a este m�todo se le va a llamar cuando muere el caza.
	// - desactivar los asteroides y las balas, actualizar el estado del juego, etc.
	void onFighterDeath();
	// - a este m�todo se le va a llamar cuando no haya m�s asteroides.
	// - desactivar todas las balas, etc.
	void onAsteroidsExtinction();

};