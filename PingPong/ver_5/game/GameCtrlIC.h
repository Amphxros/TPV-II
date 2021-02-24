// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "InputComponent.h"

class GameManager;

class GameCtrlIC: public InputComponent {
public:
	GameCtrlIC();
	virtual ~GameCtrlIC();
	void handleInput(Container *c) override;
private:
	void moveBall(GameManager *gm);

};

