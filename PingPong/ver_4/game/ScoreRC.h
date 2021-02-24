// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "RenderComponent.h"

class ScoreRC: public RenderComponent {
public:
	ScoreRC();
	virtual ~ScoreRC();
	void render(Container *c) override;
};

