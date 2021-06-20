// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <cstdint>

#include "../ecs/System.h"

class Texture;

class RenderSystem: public System {
public:
	RenderSystem();
	virtual ~RenderSystem();
	void init() override;
	void update() override;
	void receive(const Message&) override;

private:
	void drawMsgs();
	void drawRounds();
	void drawEntitiesWithImage();

	bool isRunning_;
	bool isGameOver_;
	bool isNewGame_;
	bool pacmanWon_;
	unsigned short int remainingRounds_;

	Texture *roundImg_;
	Texture *winnerMsg_;
	Texture *loserMsg_;
	Texture *gameOverMsg_;
	Texture *continueMsg_;
	Texture *startMsg_;
};
