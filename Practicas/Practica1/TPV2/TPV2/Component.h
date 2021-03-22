#pragma once
#include "ecs.h"
#include "utils/Vector2D.h"
#include "sdlutils/Texture.h"
class Entity;
class Manager;
class Component
{
public:
	Component() :id_(), entity_(nullptr) {}
	Component(ecs::CmpID id) : id_(id), entity_(nullptr) {}
	virtual ~Component() { }

	inline void setEntity(Entity* e) { entity_ = e; }
	inline ecs::CmpID getID() { return id_; }

	//metodos a heredar
	virtual void init() {};
	virtual void update() {};
	virtual void render() {};
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
	Transform(Vector2D pos, Vector2D vel, double width, double height, double rotation);
	virtual ~Transform() {};

	void update() override;

	//get y set por aqui
	inline double getW() { return w_; }
	inline void setW(double w) { w_ = w; }

	inline double getH() { return h_; }
	inline void setH(double h) { h_ = h; }

	inline double getRotation() { return rot_; }
	inline void setRotation(double rot) { rot_ = rot; }

	inline Vector2D getPos() { return pos_; }
	inline void setPos(Vector2D p) { pos_.set(p); }
	inline void setPos(double x, double y) { pos_.set(x, y); }

	inline Vector2D getVel() { return vel_; }
	inline void setVel(Vector2D v) { vel_.set(v); }
	inline void setVel(double x, double y) { vel_.set(x, y); }


private:
	double w_, h_, rot_;
	Vector2D pos_, vel_;
};

class DeAcceleration : public Component {
public:
	DeAcceleration(double deAcceleration);
	virtual ~DeAcceleration();
	virtual void init() override;
	virtual void update() override;
private:
	double deAccel_;
	Transform* tr_;
};

class Image : public Component {
public:
	Image() : Component(ecs::CmpID::Image), texture_(nullptr), tr_(nullptr) {};
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
	Health(int num, Texture* texture);

	virtual ~Health() {}
	virtual void init() override;
	virtual void render() override;
	inline int getNumVidas() { return num_; }
	inline void setNumVidas(int num) { num_ = num; }
	inline void resetNumVidas() { num_ = maxVidas_; }

private:
	int maxVidas_;
	int num_;

	Texture* texture_;

};

class FighterCtrl : public Component {
public:
	FighterCtrl();
	virtual ~FighterCtrl() {}
	virtual void init() override;
	virtual void update() override;
private:
	Transform* tr_;

};

class Gun : public Component {
public:
	Gun();
	Gun(uint32_t time);
	virtual ~Gun() {}
	virtual void init() override;
	virtual void update()override;

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
	FramedImage(Texture* texture, int nRows, int nCols, int posX, int posY, float framerate);
	virtual ~FramedImage();
	virtual void init() override;
	virtual void render() override;
	virtual void update() override;

private:
	Transform* tr_;
	Texture* texture_;
	SDL_Rect src_;

	Vector2D tam;
	Vector2D ini;

	int nRows_, nCols_, pos_X, pos_Y, width, height;
	float framerate_;
};

class Generations : public Component {
public:
	Generations();
	Generations(int gen);
	virtual ~Generations() {}
	void setGen(int gen);
	void resetGen();
	inline int genGen() { return gen_; }

private:
	int gen_;
};

//class Follow : public Component {
//public:
//private:
//};

//Bala: Transform, Image, DisableOnExit

class DisableOnExit : public Component {
public:
	DisableOnExit(int width, int height);
	virtual ~DisableOnExit();

	virtual void update() override;
private:
	int width_, height_;
};
//GameManager: State, GameCtrl, AsteroidsManager, CollisionsManager

class State {
public:
	enum GameState { NEWGAME, PAUSED, RUNNING, GAMEOVER };
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

class AsteroidsManager : public Component {
public:
	AsteroidsManager();
	AsteroidsManager(int numAsteroids, int time, int width, int height);
	void update();
	void render();

private:
	void createAsteroids(int nGen);
	Transform* tr_;
	Manager* mngr_;
	int num_asteroids, time_, lastTime_, gen_;
	float width_, height_;
};

class CollisionsManager : public Component {
public:
private:
};