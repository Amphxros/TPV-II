#include "Health.h"

Health::Health(int health, Texture* tex):
	Component(),health_(health), tex_(tex)
{
	currHealth_ = health_;
}

Health::~Health()
{
}

void Health::render()
{
	for(int i=0; i<currHealth_; i++){
		SDL_Rect dest;
		dest.x = sdlutils().width()/2 -120 + 35 * i;
		dest.y = 10;
		dest.w = 30;
		dest.h = 30;

		tex_->render(dest, 0.0f);

	}
}
