#pragma once
#include "../ecs/Component.h"

class Generations : public Component{

public:

	Generations(){}
	Generations(int gen);
	virtual ~Generations();

	inline void setGen(int gen) { gen_ = gen; }
	inline int getGen() { return gen_; }

private:

	int gen_;

};