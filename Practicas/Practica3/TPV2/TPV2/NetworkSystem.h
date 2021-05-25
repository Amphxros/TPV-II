#pragma once

#include <SDL_net.h>
#include <SDL_stdinc.h>
#include <array>

#include "msg.h"
#include "System.h"

class Vector2D;
class Manager;
class NetworkSystem :
	public System
{
public:
	NetworkSystem(const char* host, Uint16 port, std::string playerName);
	virtual ~NetworkSystem();
	void init() override;
	void update() override;

	inline bool isMaster() {	return isMaster_;	}
	inline bool isGameReady() {	return isGameReady_;	}
	inline Uint8 getId() {return id_;}

	// Estado del juego
	void sendStateChanged(Uint8 state, Uint8 left_score, Uint8 right_score);
	void sendStartGameRequest();
	// Posiciones de los elementos del juego
	void sendFighterPosition(Vector2D pos);
	void sendBulletInfo(Vector2D pos, Vector2D vel);
	auto& getNames() {
		return names_;
	}
	void switchId() {
		if (isMaster_ && !isGameReady_) {
			id_ = 1 - id_;
			std::swap(names_[0], names_[1]);
		}
	}
	
protected:

	const char* host_;
	Uint16 port_;
	bool isMaster_;
	bool isGameReady_;
	Uint8 id_;
	UDPsocket conn_;
	UDPpacket* p_;
	msg::Message* m_;
	IPaddress otherPlayerAddress_;
	std::string localPlayerName_;
	std::string remotePlayerName_;
	std::array<std::string, 2> names_;
	Uint32 lastTimeActive_;
	
};

