#pragma once

class Entity;
#include "utils/Vector2D.h"
namespace msg {
	using msgType = std::size_t;
	enum msgID : msgType {
		START_GAME,
		GAMEOVER,
		ROUNDOVER,
		COLLISIONBULLET,
		COLLISIONFIGHTER,
		BULLET_SHOOT,
		lastMsgid
	};

	struct Collision {
		Entity* a;
		Entity* b;
	};

	struct GameInfo {
		int currHealth;
		bool gameWin;
		int state;
	};
	
	struct AsteroidInfo {
		int n;
	};


	struct BulletInfo
	{
		Vector2D p, v;
		double w, h, r;
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
			GameInfo info;
			AsteroidInfo num;
			BulletInfo bullet;
		};
	};


}