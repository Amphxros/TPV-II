#include "NetworkSystem.h"

NetworkSystem::NetworkSystem(const char* host, Uint16 port, std::string playerName)
{
}

NetworkSystem::~NetworkSystem()
{
}

void NetworkSystem::init()
{
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
