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
		
		msg::PlayRequestMsg* m = static_cast<msg::PlayRequestMsg*>(m_);
		m->id_ = msg::MsgID::START_REQUEST;
		memset(m->name_,0,10);
		auto size = localPlayerName_.length() > 9 ? 9 : localPlayerName_.length();
		memcpy(m->name_, localPlayerName_.c_str(), size);
		p_->len = sizeof(msg::PlayRequestMsg);
		p_->address = otherPlayerAddress_;
		SDLNet_UDP_Send(conn_, -1, p_);

		// we use socket set to allow waiting for response instead of just looping
		SDLNet_SocketSet socketSet = SDLNet_AllocSocketSet(1);
		SDLNet_UDP_AddSocket(socketSet, conn_);
		
		if (SDLNet_CheckSockets(socketSet, 3000)) {
			if (SDLNet_SocketReady(conn_)) {
				if (SDLNet_UDP_Recv(conn_, p_) > 0) {
					if (m_->id_ == msg::CONNECTED) {
						isGameReady_ = true;
						msg::ConnectedMsg* c = static_cast<msg::ConnectedMsg*>(m_);
						remotePlayerName_ = std::string(reinterpret_cast<char*>(m->name_));
						id_ = m->id_;
						names_[id_] = localPlayerName_;
						names_[1 - id_] = remotePlayerName_;
					}
				}
			}
		}

		SDLNet_FreeSocketSet(socketSet);
		if (isGameReady_)
			throw "ERROR AL CONNECTAR";
	}

}

void NetworkSystem::update()
{
	while (SDLNet_UDP_Recv(conn_, p_)) {
		lastTimeActive_ = SDL_GetTicks();
		switch (m_->id_) {
		case msg::MsgID::START_REQUEST:
			if (isMaster_) {
				//enviar al gamesys el cambio
			}
			break;
		case msg::MsgID::BULLET_SHOT:
			
			break;

		}
	}
}

void NetworkSystem::sendStateChanged(Uint8 state, Uint8 left_score, Uint8 right_score)
{
	if (!isGameReady_) {
		return;
	}
	else {

	}
}

void NetworkSystem::sendStartGameRequest()
{
	m_->id_ = msg::START_REQUEST;
	p_->len = sizeof(msg::Message);
	p_->address = otherPlayerAddress_;
	SDLNet_UDP_Send(conn_, -1, p_);
}

void NetworkSystem::sendFighterPosition(Vector2D pos)
{
	if (!isGameReady_) {
		return;
	}
	else {
		msg::FighterInfo* f = static_cast<msg::FighterInfo*>(m_);
		f->id_ = msg::FIGHTER_INFO;
		f->x_ = pos.getX();
		f->y_ = pos.getY;
		f->rot_ = 0; //añadir parametros


		p_->len = f->size_;
		p_->address = otherPlayerAddress_;
		//send
		SDLNet_UDP_Send(conn_, -1, p_);

	}
}

void NetworkSystem::sendBulletInfo(Vector2D pos, Vector2D vel)
{
	if (!isGameReady_) {
		return;
	}
	else {
		msg::BulletShoot* b = static_cast<msg::BulletShoot*>(m_);
		b->id_ = msg::MsgID::BULLET_SHOT;
		b->x_ = pos.getX();
		b->y_ = pos.getX();
		b->velX_ = vel.getX();
		b->velY_ = vel.getX();
		p_->len = b->size_;
		p_->address = otherPlayerAddress_;
		SDLNet_UDP_Send(conn_, -1, p_);
	}
}
