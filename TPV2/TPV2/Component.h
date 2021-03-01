#pragma once
#include "ecs.h"
class Entity;
class Component
{
public:
	Component():id_(), entity_(nullptr) {}
	Component(ecs::CmpID id): id_(id) {}
	virtual ~Component() { }

	inline void setEntity(Entity* e) { entity_ = e; }
	inline ecs::CmpID getID() { return id_; }

	//metodos a heredar
	virtual void init() { }
	virtual void update() { }
	virtual void render() { }
	virtual void handleInput(){ }
protected:
	Entity* entity_;
	ecs::CmpID id_;
};

//COMPONENTES
// Implementar todos los componenetes

// Caza: Transform, DeAcceleration, Image, Health, FighterCtrl, Gun, ShowAtOpposieSide
class Transform : public Component {

};

class DeAcceleration : public Component {

};

class Image : public Component {

};

class Health : public Component {

};

class FighterCtrl : public Component {

};

class Gun : public Component {

};
class ShowAtOpposieSide : public Component {

};


// Asteroides: Transform, FramedImage, ShowAtOpposieSide, Generations, Follow

class FramedImage : public Component {

};

class Generations : public Component {

};

class Follow : public Component {

};

//Bala: Transform, Image, DisableOnExit

class DisableOnExit : public Component {

};

//GameManager: State, GameCtrl, AsteroidsManager, CollisionsManager

class State : public Component {

};
class GameCtrl : public Component {

};

class AsteroidsManager : public Component {

};

class CollisionsManager : public Component {

};