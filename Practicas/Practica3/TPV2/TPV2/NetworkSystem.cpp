#include "NetworkSystem.h"
#include "Manager.h"

NetworkSystem::NetworkSystem(const char* host, Uint16 port, std::string playerName): 
	System(ecs::NetWorkSys),
	host_(host), port_(port), isMaster_(false),//
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

	if (host_ == nullptr) { //si empezamos el juego como host
		isMaster_ = true;
		id_ = 0;
		conn_ = SDLNet_UDP_Open(port_);
		if (!conn_)
			throw SDLNet_GetError();

		names_[0] = localPlayerName_;
		names_[1] = remotePlayerName_;
	}
	else { //si vamos como cliente
		isMaster_ = false;
		//id_=1;


		conn_ = SDLNet_UDP_Open(0);
		if (!conn_) {
			std::cout << "Cant connect to " << host_ << ":"
				<< port_ << std::endl;
		}

		std::cout << "Trying to connect to other player at " << host_ << ":"
			<< port_ << std::endl;
		// resolve the host name into an IPAdrress

		if (SDLNet_ResolveHost(&otherPlayerAddress_, host_, port_) < 0) {
			std::cout << "Connection failed" << host_ << ":" << port_ << std::endl;
			throw SDLNet_GetError();
		}

		msg::PlayRequest* p = static_cast<msg::PlayRequest*>(m_);
		p->type = msg::I_WANT_PLAY;
		memset(p->name, 0, 10);

		auto size = localPlayerName_.length() > 9 ? 9:localPlayerName_.length();

		memcpy(p->name, localPlayerName_.c_str(), size);
		p_->len = sizeof(msg::PlayRequest);
		p_->address = otherPlayerAddress_;
		SDLNet_UDP_Send(conn_, -1, p_);

		SDLNet_SocketSet socketSet = SDLNet_AllocSocketSet(1);
		SDLNet_UDP_AddSocket(socketSet, conn_);

		if (SDLNet_CheckSockets(socketSet, 30000)) {
			std::cout << "Connecting to" << host_ << ":" << port_ << std::endl
				assert(conn_ != true);
		
			if (SDLNet_SocketReady(conn_)) {
				std::cout << "Socket Ready" << host_ << ":" << port_ << std::endl;
				assert(p_!=nullptr);
		
				if (SDLNet_UDP_Recv(conn_, p_) > 0) {
					std::cout << "Connected" << host_ << ":" << port_ << std::endl;
					isGameReady_ = true;
					msg::Welcome* w = static_cast<msg::Welcome*>(m_);
					remotePlayerName_ = std::string(reinterpret_cast<char*>(w->name));
					id_ = m_->type;
					names_[id_] = localPlayerName_;
					names_[1 - id_] = remotePlayerName_;
				}

			}

		}

		assert(isGameReady_ != true);
		// free the socket set, won't be used anymore
		SDLNet_FreeSocketSet(socketSet);
		// if did not succeed to connect, throw an exception
		if (!isGameReady_) {
			throw "ERROR AL CONECTAR";
		}
	}

}

void NetworkSystem::update()
{
	while (SDLNet_UDP_Recv(conn_, p_)) {
		lastTimeActive_ = SDL_GetTicks();
		switch (m_->type) {
		case msg::_START_REQUEST:
			if (isMaster_ && isGameReady_) {
			mngr->getSystem<GameCtrlSystem>(ecs::GameCtrlSys)->start();
			}
			break;
		case msg::I_WANT_PLAY:
			// we accept the connection if the player is the master, and no other player is connected
			if (isMaster_ && !isGameReady_) {
				msg::PlayRequest *m = static_cast<msg::PlayRequest*>(m_);
				otherPlayerAddress_ = p_->address;
				remotePlayerName_ = std::string(
						reinterpret_cast<char*>(m->name));
				names_[1 - id_] = remotePlayerName_;
				msg::Welcome *mr = static_cast<msg::Welcome*>(m_);

				mr->type = msg::_WELCOME;
				auto size =
						localPlayerName_.size() > 9 ?
								9 : localPlayerName_.size();
				memcpy(mr->name, localPlayerName_.c_str(), size);
				mr->type = 1 - id_;
				p_->len = sizeof(msg::Welcome);
				SDLNet_UDP_Send(conn_, -1, p_);
				isGameReady_ = true;
			}
			break;
		}
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
	m_->type = msg::_START_REQUEST;
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
		//msg::FighterInfo* f = static_cast<msg::FighterInfo*>(m_);
		//f->id_ = msg::FIGHTER_INFO;
		//f->x_ = pos.getX();
		//f->y_ = pos.getY();
		//f->rot_ = 0; //añadir parametros


		//p_->len = f->size_;
		//p_->address = otherPlayerAddress_;
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
		//msg::BulletShoot* b = static_cast<msg::BulletShoot*>(m_);
		//b->id_ = msg::MsgID::BULLET_SHOT;
		//b->x_ = pos.getX();
		//b->y_ = pos.getX();
		//b->velX_ = vel.getX();
		//b->velY_ = vel.getX();
		//p_->len = b->size_;
		p_->address = otherPlayerAddress_;
		SDLNet_UDP_Send(conn_, -1, p_);
	}
}
