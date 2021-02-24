// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "RenderComponent.h"

class CtrlMsgRC: public RenderComponent {
public:
	CtrlMsgRC();
	virtual ~CtrlMsgRC();
	void render(Container *c) override;
};

