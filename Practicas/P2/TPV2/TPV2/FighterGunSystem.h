#pragma once

#include "ecs/System.h"

class FighterGunSystem : public System
{
public:
	FighterGunSystem();
	virtual ~FighterGunSystem();
	
	// - si el juego está parado no hacer nada. Si el jugador pulsa SDLK_S, llamar
	// a shoot del BulletsSystem para añadir una bala al juego, etc.
	// - se puede incluir ese comportamiento en el FighterSystem directamente en
	// lugar de definirlo en un sistema separado

	virtual void init() override;
	virtual void update() override;
	virtual void receive(const Message& m) override;

private:
	bool active_;

};