#pragma once
#include "ecs.h"
#include "utils/Vector2D.h"
#include "utils/Collisions.h"
#include "sdlutils/SDLUtils.h"
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

//Resto de componentes
class Transform : public Component {
public:
	Transform();
	Transform(Vector2D pos, Vector2D vel, double width, double height, double rotation);
	virtual ~Transform() {};

	void update() override;

	//get y set del ancho
	inline double getW() { return w_; }
	inline void setW(double w) { w_ = w; }

	//get y set del alto 
	inline double getH() { return h_; }
	inline void setH(double h) { h_ = h; }

	//get y set de la rotacion
	inline double getRotation() { return rot_; }
	inline void setRotation(double rot) { rot_ = rot; }

	//get y set de la posicion
	inline Vector2D getPos() { return pos_; }
	inline void setPos(Vector2D p) { pos_.set(p); }
	inline void setPos(double x, double y) { pos_.set(x, y); }

	//get y set de la velocidad
	inline Vector2D getVel() { return vel_; }
	inline void setVel(Vector2D v) { vel_.set(v); }
	inline void setVel(double x, double y) { vel_.set(x, y); }


private:
	double w_, h_, rot_; //ancho, alto y rotacion
	Vector2D pos_, vel_; // posicion y velocidad
};

class DeAcceleration : public Component {
public:
	DeAcceleration(double deAcceleration);
	virtual ~DeAcceleration();
	virtual void init() override;
	virtual void update() override;
private:
	double deAccel_; //deacceleracion
	Transform* tr_; //transform de la entidad
};

class Image : public Component {
public:
	Image() : Component(ecs::CmpID::Image), texture_(nullptr), tr_(nullptr) {};
	Image(Texture* t);
	virtual ~Image() { };
	virtual void init() override;
	virtual void render() override;
private:
	Texture* texture_; //textura de la entidad a dibujar
	Transform* tr_; //transform de la entidad
};

class Health : public Component {
public:
	Health();
	Health(int num);
	virtual ~Health() {}
	virtual void init() override;
	virtual void render() override;

	// Utilidades para calculos de las vidas con las colisiones
	inline int getNumVidas() { return num_; }
	inline void setNumVidas(int num) { num_ = num; }
	inline void resetNumVidas() { num_ = maxVidas_; }

private:
	int maxVidas_;	// Cantidad inicial de vidas
	int num_;		// Cantidad actial de vidas

	Texture* texture_; //textura de las vidas

};

class FighterCtrl : public Component {
public:
	FighterCtrl();
	FighterCtrl(double thrust);
	virtual ~FighterCtrl() {}
	virtual void init() override;
	virtual void update() override;

	void resetPos();
private:
	Transform* tr_; //transform de la entidad
	double thrust_; //thrust 
	Vector2D pos_ini; //posicion inicial para resetear la posicion

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
	uint32_t time_;		// Variable tiempo para el recorrido de la bala
	uint32_t curr_time_, lastTime_;
	Manager* mngr_;		//manager para crear las balas


};
class ShowAtOppositeSide : public Component {
public:
	ShowAtOppositeSide();
	ShowAtOppositeSide(int width, int height);
	virtual ~ShowAtOppositeSide() {}
	virtual void init() override;
	virtual void update() override;

private:
	Transform* tr_; //transform de la entidad
	int width_; //ancho 
	int height_; //alto
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
	Transform* tr_; //trnsform de la entidad
	Texture* texture_; //textura a dibujar
	SDL_Rect src_; 

	Vector2D tam; //tamaño de la textura
	Vector2D ini; //frame inicial

	int nRows_, nCols_, pos_X, pos_Y, width, height; //num de filas, columnas, frame actual y tamaño del frame
	float framerate_; //cantidad de milisegundos que se cambia el frame
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
	int maxgen_; //num maximo de generaciones
	int gen_;	//numero actual de generaciones
};

class Follow : public Component {
public:
	Follow();

	virtual void init() override;
	virtual void update() override;

private:
	Transform* tr_; //transform de la entidad
	Transform* posPlayer;	// Posicion del jugador para seguirle
};


class DisableOnExit : public Component {
public:
	DisableOnExit(int width, int height);
	virtual ~DisableOnExit();
	virtual void init() override;
	virtual void update() override;
private:
	int width_, height_; //ancho y alto para tener un margen
	Transform* tr_; //transform de la entidad
};


