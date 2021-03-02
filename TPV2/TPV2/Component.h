#pragma once
#include "ecs.h"
#include "utils/Vector2D.h"
#include "sdlutils/Texture.h"
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
public:
	Transform() : Component(ecs::CmpID::Transform) {};
	Transform(Vector2D pos, double width, double height);
	virtual ~Transform() {};

	//get y set por aqui
	inline double getW() { return w_; }
	inline double getH() { return h_; }
	inline Vector2D getPos() { return pos_; }

	inline void setW(double w) { w_ = w; }
	inline void setH(double h) { h_ = h; }
	inline void setPos(Vector2D pos) { pos_.set(pos); }

private:
	double w_, h_;
	Vector2D pos_;
};

class DeAcceleration : public Component {

};

class Image : public Component {
public:
	Image();
	Image(Texture* t, Transform* tr);
	virtual ~Image() { delete texture_; delete tr_; };
	virtual void render() override;
private:
	Texture* texture_;
	Transform* tr_;
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