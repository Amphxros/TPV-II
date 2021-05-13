#include "NetworkSystem.h"

NetworkSystem::NetworkSystem(const char* host, Uint16 port, std::string playerName): 
	System(ecs::NetWorkSys),host_(host), port_(port), isMaster_(false), //
	isGameReady_(false), id_(0), conn_(), p_(nullptr), m_(nullptr), //
	otherPlayerAddress_(), localPlayerName_(playerName), remotePlayerName_("N/A"), lastTimeActive_(0) { }

NetworkSystem::~NetworkSystem()
{
}

void NetworkSystem::init()
{
	if (SDLNet_Init() < 0)
		throw "ERROR NOT CONNECTED";

	p_ = SDLNet_AllocPacket(100);
	m_ = reinterpret_cast<msg::Message*>(p_->data);

	if(host_==nullptr){
		isMaster_ = true;
		id_ = 0;
		conn_ = SDLNet_UDP_Open(port_);
		if (!conn_)
			throw "ERROR CATASTROFICO";

		names_[0] = localPlayerName_;
		names_[1] = remotePlayerName_;
	}
	else{
		isMaster_ = false;
		id_ = 1;
		conn_ = SDLNet_UDP_Open(0);
		if(!conn_)
			throw "ERROR CATASTROFICO";
		std::cout << "Trying to connect to other player at " << host_ << ":"
				<< port_ << std::endl;
	
		// resolve the host name into an IPAdrress
		if (SDLNet_ResolveHost(&otherPlayerAddress_, host_, port_) < 0) {
			throw SDLNet_GetError();
		}


	}

}

void NetworkSystem::update()
{
}

void NetworkSystem::sendStateChanged(Uint8 state, Uint8 left_score, Uint8 right_score)
{
}

void NetworkSystem::sendStartGameRequest()
{
}

void NetworkSystem::sendFighterPosition(Vector2D pos)
{
}

void NetworkSystem::sendBulletInfo(Vector2D pos, Vector2D vel)
{
}
