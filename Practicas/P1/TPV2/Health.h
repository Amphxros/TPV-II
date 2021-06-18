#pragma once
#include "ecs/Component.h"
#include "sdlutils/Texture.h"
#include "sdlutils/SDLUtils.h"

class Health :public Component {

public:

	Health() {};
	Health(int health, Texture* tex);
	virtual ~Health();

	virtual void render() override;

	inline void setHealth(int h) { currHealth_ = h; }
	inline int getHealth() { return currHealth_; }
	inline void resetHealth() { currHealth_ = health_; }

private:

	int currHealth_, health_;
	Texture* tex_;

};