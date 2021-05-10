#pragma once
#include <cstdint>
namespace msg
{
	using msgSizeType = uint32_t;

	enum MsgID : uint8_t {
		CONNECTED,
		CONNECTION_REFUSED,
		CLIENT_DISCONNECTED,
		START_REQUEST,
		START_GAME,
		PLAYER_INFO,
		BULLET_SHOT,
		COLLISION,
		FIGHTER_INFO,
		FIGHTER_DEATH,
		_last_msgID
	};

	struct Message
	{
		Message(msgSizeType size, MsgID id): size_(size),senderClientID(0), id_(id){}
		msgSizeType size_;
		uint32_t senderClientID;
		MsgID id_;
	};

	struct ConnectedMsg : public Message {
		ConnectedMsg(int clientID) :
			Message(sizeof(ConnectedMsg), CONNECTED), clientID_(clientID) {}

		uint32_t clientID_;
	};
	struct ClientDisconnectedMsg: public Message
	{
		ClientDisconnectedMsg(uint32_t clientID) : Message(sizeof(ClientDisconnectedMsg),CLIENT_DISCONNECTED), clientID_(clientID){}
		uint32_t clientID_;
	};
	struct  BulletShoot: public Message
	{
		BulletShoot(double x, double y, double velX, double velY, double w, double h):
			Message(sizeof(BulletShoot), BULLET_SHOT), x_(x), y_(y), velX_(velX), velY_(velY), w_(w),h_(h){}
		double x_, y_, velX_, velY_, w_, h_;
	};

	struct FighterInfo: public Message
	{
		FighterInfo(double x, double y, double rot) :
			Message(sizeof(FighterInfo), FIGHTER_INFO),x_(x), y_(y),rot_(rot){}

			double x_, y_, rot_;
	};
	struct  FighterDeath : public Message
	{
		FighterDeath(uint8_t id) : Message(sizeof(FighterDeath) FIGHTER_DEATH), id_(id){}
		uint8_t id_;
	};
};

