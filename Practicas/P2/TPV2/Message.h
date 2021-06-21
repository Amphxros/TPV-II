#pragma once

#include "utils/Vector2D.h"

class Entity;

namespace msg {
	using msgType = std::size_t;
	enum msgID : msgType {
		START_GAME,
		INIT_GAME,
		GAMEOVER,
		ROUNDOVER,
		COLLISIONBULLET,
		COLLISIONFIGHTER,
		BULLET_SHOOT,
		NO_MORE_ASTEROIDS,
		lastMsgid
	};

	struct Collision {
		Entity* a; //a de asteroid
		Entity* b; //b de bullet aunque tambien puede ser el fighter, pero en general es para discernir la bala del asteroide

	};

	struct AsteroidInfo {
		int n; //num de asteroides a añadir
	};


	struct BulletInfo
	{
		Vector2D p, v; //posicion y velocidad
		double w, h, r; //ancho alto y rotacion
	};

	struct GameInfo {
		int currState; //new=0, running=1, pause=2, gameover=3, 
		bool hasWon; //indica si el jugador ha ganado
	};
	struct Message
	{
		Message() {

		}
		~Message() {

		}
		msgID id;
		union {
			Collision col;
			AsteroidInfo num;
			GameInfo info;
			BulletInfo bullet;
		};
	};
}