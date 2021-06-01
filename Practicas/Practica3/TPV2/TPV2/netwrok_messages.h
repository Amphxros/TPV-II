// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "network_types.h"

#pragma pack(push,1)

enum MsgType : uint8_nt {
	_NONE_ = 0, //
	_I_WANT_TO_PLAY_, //
	_WELCOME_, //
	_FighterPos,
	_START_GAME_REQUEST_,
	_STATE_CHANGED_, //
	_DISCONNECTED_, //
	_Shoot, //
	_ACTIVE_
};

struct NetworkMessage {
	uint8_nt _type;
};

struct DissConnectMsg: NetworkMessage {
	uint8_nt id;
};


struct PlayRequestMsg: NetworkMessage {
	uint8_nt name[10];
};

struct WelcomeMsg: NetworkMessage {
	uint8_nt id;
	uint8_nt name[10];
};

struct FighterPositionMsg: NetworkMessage {
	uint8_nt id;
	float32_nt x;
	float32_nt y;
	float32_nt rotation;
};

struct StateChangedMessage: NetworkMessage {
	uint8_nt state_;
	uint8_nt left_score_;
	uint8_nt right_score_;
};

struct ShootMsg : NetworkMessage {
	float32_nt pos_x;
	float32_nt pos_y;
	float32_nt vel_x;
	float32_nt vel_y;
	float32_nt w;
	float32_nt h;
};


#pragma pack(pop)
