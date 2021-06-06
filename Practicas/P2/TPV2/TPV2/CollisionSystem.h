#pragma once

#include "ecs/System.h"

class CollisionSystem : public System
{
public:
	CollisionSystem();
	virtual ~CollisionSystem();
	// - si el juego est� parado no hacer nada.
	// - comprobar colisiones como en la pr�ctica 1 y avisar a los sistemas
	// correspondientes en caso de colisiones
	void update() override;

	void receive(const Message& m) override;

private:
	bool active_;
};