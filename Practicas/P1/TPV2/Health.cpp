#include "Health.h"

Health::Health(int health, Texture* tex):
	Component(),health_(health), tex_(tex)
{
}

Health::~Health()
{
}

void Health::render()
{
	for(int i=0; i<health_; i++){
		SDL_Rect dest;
		dest.x = sdlutils().width() / 3 + (tex_->width() + 10) * i;
		dest.y = tex_->height();
		dest.w = tex_->width();
		dest.h = tex_->height();

		tex_->render(dest, 0.0f);

	}
}
