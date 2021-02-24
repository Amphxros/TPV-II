// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "InputComponent.h"

class PaddleMouseCtrlIC: public InputComponent {
public:
	PaddleMouseCtrlIC();
	virtual ~PaddleMouseCtrlIC();
	void handleInput(Container *c) override;
};

