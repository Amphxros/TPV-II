#pragma once
#include "ecs/System.h"
#include <cstddef>
#include "utils/Vector2D.h"
#include "Message.h"
class Entity;
class BulletsSystem :
	public System
{
public:
	BulletsSystem();
	virtual ~BulletsSystem();

	virtual void init() override;
	virtual void update() override;
	virtual void receive(const msg::Message& m) override;

private:
	//estos metodos son privdos porque al comunicarse con mensajes se avisan en el receive 
	void onCollisionWithAsteroid(Entity* a, Entity* b);
	void shoot(Vector2D pos, Vector2D vel, double width, double height, double rotation);
};

