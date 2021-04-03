#pragma once
#include "ecs.h"
#include "utils/Vector2D.h"
#include "sdlutils/Texture.h"
#include "utils/Collisions.h"
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
	virtual ~Image() { };
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
	FighterCtrl(double thrust);
	virtual ~FighterCtrl() {}
	virtual void init() override;
	virtual void update() override;
	void setActive(bool act) { isActive = act; }
private:
	Transform* tr_;
	double thrust_;

	bool isActive;
};

class Gun : public Component {
public:
	Gun();
	Gun(uint32_t time);
	virtual ~Gun() {}
	virtual void init() override;
	virtual void update()override;
	void setActive(bool act) { isActive = act; }
private:
	Transform* tr_;
	uint32_t time_;
	uint32_t curr_time_;
	Manager* mngr_;

	bool isActive;

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
	void resetGen();
	inline void setGen(int gen) { gen_ = gen; };
	inline int getGen() { return gen_; }

private:
	int maxgen_;
	int gen_;
};

class Follow : public Component {
public:
	Follow();

	virtual void init() override;
	virtual void update() override;

private:
	Transform* tr_;
	Transform* posPlayer;
};

//Bala: Transform, Image, DisableOnExit

class DisableOnExit : public Component {
public:
	DisableOnExit(int width, int height);
	virtual ~DisableOnExit();
	virtual void init() override;
	virtual void update() override;
private:
	int width_, height_;
	Transform* tr_;
};
//GameManager: State, GameCtrl, AsteroidsManager, CollisionsManager


class State : public Component {
public:
	enum GameState { NEWGAME, PAUSED, RUNNING, GAMEOVER };
	State();
	virtual ~State();
	virtual void init() override;
	virtual void render() override;

	inline void setState(GameState s) { gs = s; }
	inline bool isGameRunning() { return gs == GameState::RUNNING; }
	inline bool isGameNew() { return gs == GameState::NEWGAME; }
	inline bool isGamePaused() { return gs == GameState::PAUSED; }
	inline bool isGameOver() { return gs == GameState::GAMEOVER; }
private:
	GameState gs;

	Texture* startMsg;
	Texture* continueMsg;
	Texture* gameOverMsg;

};

class AsteroidsManager : public Component {
public:
	AsteroidsManager();
	AsteroidsManager(int numAsteroids, int time, int width, int height);
	virtual ~AsteroidsManager() {}
	virtual void init() override;
	virtual void update() override;
	void createAsteroids();
	void OnCollision(Entity* A);

private:
	void createAsteroid(int nGen);
	Manager* mngr_;
	State* state_;
	int num_asteroids, time_, lastTime_, gen_;
	float width_, height_;
};
class GameCtrl : public Component {
public:
	GameCtrl();
	virtual ~GameCtrl() {}
	virtual void init() override;
	virtual void update() override;

private:
	State* state_;
	AsteroidsManager* astManager_;
	Manager* mngr_;

};
class CollisionsManager : public Component {
public:
	CollisionsManager();
	virtual ~CollisionsManager(){}
	virtual void init() override;
	virtual void update() override;

private:

	bool isOnCollision(Transform* t, Transform* other);


	AsteroidsManager* ast;

	Entity* fighter_;
	Health* health_;
	State* state_;

	Transform* fighterTr_;


};