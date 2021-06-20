// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/System.h"

class FoodSystem: public System {
public:
	FoodSystem();
	virtual ~FoodSystem();
	void init() override;
	void receive(const Message&) override;
	void update() override;
private:
	void handlePacManCollidesWithFood(const Message &m);
	void initFood();
	void removeAllFood();

	unsigned short int numOfFoodPieces_;
};

