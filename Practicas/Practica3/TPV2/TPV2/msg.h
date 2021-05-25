#pragma once
#include <cstdint>
namespace msg
{
	using msgSizeType = uint32_t;

	enum MsgID : uint8_t {
		NONE = 0,
		I_WANT_PLAY,
		_WELCOME,
		_FIGHTER_POS,
		_START_REQUEST,
		_STATE_CHANGED,
		_BULLET_INFO,
		_DISCONNECTED,
		_ACTIVE_,

		_last_msgID
	};

	struct Message {
		uint8_t type;
	};
	struct Disconnected: Message {
		uint8_t id_;
	};
	struct PlayRequest: Message {
		uint8_t name[10];
	};
	struct Welcome: Message {
		uint8_t id_;
		uint8_t name[10];
	};

	struct FighterPosition: Message {
		uint8_t id_;
		uint8_t x;
		uint8_t y;
	};

	struct StateChanged: Message {
		uint8_t state_;
		uint8_t fighterAscore;
		uint8_t figherBscore;
	};

	struct BulletInfoMsg : Message {
		float pos_x;
		float pos_y;
		float vel_x;
		float vel_y;
	};





}