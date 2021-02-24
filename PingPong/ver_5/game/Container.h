// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <vector>
#include "GameObject.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"

class Container: public GameObject {
public:
	Container();
	virtual ~Container();
	void addComponent(InputComponent *c) {
		inputC_.push_back(c);
	}
	void addComponent(PhysicsComponent *c) {
		physicsC_.push_back(c);
	}
	void addComponent(RenderComponent *c) {
		renderC_.push_back(c);
	}

	void update() override;
	void render() override;
	void handleInput() override;

private:
	std::vector<InputComponent*> inputC_;
	std::vector<PhysicsComponent*> physicsC_;
	std::vector<RenderComponent*> renderC_;
};

