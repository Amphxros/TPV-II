#pragma once
#include "ecs.h"
#include "utils/Vector2D.h"
#include "sdlutils/Texture.h"
class Entity;
class Component
{
public:
	Component():id_(), entity_(nullptr) {}
	Component(ecs::CmpID id): id_(id),entity_(nullptr) {}
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
	Transform();
	Transform(Vector2D pos,Vector2D vel, double width, double height, double rotation);
	virtual ~Transform() {};
	
	void update() override;

	//get y set por aqui
	inline double getW() { return w_; }
	inline double getH() { return h_; }
	inline double getRotation() { return rot_; }
	inline Vector2D getPos() { return pos_; }
	inline Vector2D getVel() { return vel_; }

	inline void setW(double w) { w_ = w; }
	inline void setH(double h) { h_ = h; }
	inline void setRotation(double rot) { rot_ = rot; }
	inline void setPos(Vector2D pos) { pos_.set(pos); }

private:
	double w_, h_, rot_;
	Vector2D pos_, vel_;
};

class DeAcceleration : public Component {
public:
};

class Image : public Component {
public:
	Image() : Component(ecs::CmpID::Image), texture_(nullptr), tr_(nullptr){};
	Image(Texture* t);
	virtual ~Image() { delete texture_; delete tr_; };
	virtual void init() override;
	virtual void render() override;
private:
	Texture* texture_;
	Transform* tr_;
};

class Health : public Component {
public:
	Health();
	Health(int num);
	virtual ~Health() {}
	virtual void init() override;
	inline int getNumVidas() { return num_; }
	inline void setNumVidas(int num) { num_ = num; }
	inline void resetNumVidas() { num_ = maxVidas_; }

private:
	int maxVidas_;
	int num_;
};

class FighterCtrl : public Component {
public:
	FighterCtrl();
	virtual ~FighterCtrl() {}
	virtual void init() override;
	virtual void handleInput() override;
private:
	Transform* tr_;
	
};

class Gun : public Component {
public:
	Gun();
	Gun(uint32_t time);
	virtual ~Gun() {}
	virtual void init() override;
	virtual void handleInput()override;

private:
	Transform* tr_;
	uint32_t time_;
	uint32_t curr_time_;

};
class ShowAtOppositeSide : public Component {
public:
	ShowAtOppositeSide();
	ShowAtOppositeSide(int width, int height);
	virtual ~ShowAtOppositeSide() {}
	virtual void init() override;
	virtual void update() override;

private:
	Transform* tr_;
	int width_;
	int height_;
};


// Asteroides: Transform, FramedImage, ShowAtOpposieSide, Generations, Follow

class FramedImage : public Component {
public:
private:
};

class Generations : public Component {
public:
private:
};

class Follow : public Component {
public:
private:
};

//Bala: Transform, Image, DisableOnExit

class DisableOnExit : public Component {
public:
private:
};
//GameManager: State, GameCtrl, AsteroidsManager, CollisionsManager

class State  {
public:
	enum GameState{NEWGAME, PAUSED, RUNNING, GAMEOVER};
	State();
	void update();
	void render();
private:
	GameState gs;
};
class GameCtrl {
public:
	GameCtrl(State* state);


private:
	State* state_;
};

class AsteroidsManager  {
public:
	AsteroidsManager();
	AsteroidsManager(int numAsteroids);

	void update();
	void render();

private:
	int num_asteroids;
};

class CollisionsManager : public Component {
public:
private:
};