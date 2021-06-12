#pragma once

#include "ecs/System.h"
#include "utils/Vector2D.h"
class Entity;
class BulletsSystem : public System
{
public:
	BulletsSystem();
	virtual ~BulletsSystem();
	
	// - a�adir una bala al juego, como en la pr�ctica 1. La rotaci�n de la bala
	// ser�a vel.angle(Vector2D(0.0f,-1.0f))
	void shoot(Vector2D pos, Vector2D vel, double width, double height);

	// - desactivar la bala �b�
	// - pasamos una referencia al asteroid aunque no se usa de momento (en el futuro
	// se puede usar para tener comportamientos distintos depende del tipo de
	// asteroid, etc).
	void onCollisionWithAsteroid(Entity* b, Entity* a);
	
	virtual void init() override;
	
	// - si el juego est� parado no hacer nada.
	// - mover las balas y desactivar las que se salen de la ventana
	virtual void update() override;
	
	virtual void receive(const Message& m) override;
	
private:
	bool active_;

};