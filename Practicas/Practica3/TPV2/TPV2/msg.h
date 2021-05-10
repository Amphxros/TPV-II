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

	struct  Message
	{
		Message(msgSizeType size, MsgID id): size_(size),senderClientID(0), id_(id){}
		msgSizeType size_;
		uint32_t senderClientID;
		MsgID id_;
	};


};

