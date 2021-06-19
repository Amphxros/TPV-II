// This file is part of the course TPV2@UCM - Samir Genaim

#include <SDL.h>

#include "sdlutils_demo.h"

#include "InputHandler.h"
#include "macros.h"
#include "SDLUtils.h"
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"

// include de los components
using namespace std;

void sdlutils_basic_demo() {

	// Initialise the SDLGame singleton
	SDLUtils::init("Asteroids", 800, 600,
			"resources/config/resources.json");

	// reference to the SDLUtils Singleton. You could use it as a pointer as well,
	// I just prefer to use . instead of ->, it is just a matter of taste, nothing
	// else!
	//
	// you can also use the inline method sdlutils() that simply returns the value
	// of *SDLUtils::instance() --- it is defined at the end of SDLUtils.h
	//
	auto &sdl = *SDLUtils::instance();

	//Manager* m = new Manager();
	//// store the 'renderer' in a local variable, just for convenience
	SDL_Renderer *renderer = sdl.renderer();
	

	// we can take textures from the predefined ones, and we can create a custom one as well
	
	Texture pressAnyKey(renderer, "Press any key to exit",
			sdl.fonts().at("ARIAL24"), build_sdlcolor(0x112233ff),
			build_sdlcolor(0xffffff));

	// some coordinates
	auto winWidth = sdl.width();
	auto winHeight = sdl.height();
	auto x0 = (winWidth - pressAnyKey.width()) / 2;
	auto y0 = (winHeight - pressAnyKey.height()) / 2;
	auto x1 = 0;
	auto y1 = y0 - 4 * pressAnyKey.height();
	auto y2 = y0 + 2 * pressAnyKey.height();

	// start the music in a loop
	sdl.musics().at("beat").play();

	// reference to the input handler (we could use a pointer, I just . rather than ->).
	// you can also use the inline method ih() that is defined in InputHandler.h
	auto &ih = *InputHandler::instance();

	// a boolean to exit the loop
	bool exit_ = false;
	SDL_Event event;

	while (!exit_) {
		Uint32 startTime = sdl.currRealTime();

		// update the event handler
		ih.clearState();
		while (SDL_PollEvent(&event))
			ih.update(event);

		// exit when any key is down
		if (ih.keyDownEvent())
			exit_ = true;

		// clear screen
		sdl.clearRenderer();

		// render Hello SDL
		// render Press Any Key
		pressAnyKey.render(x0, y0);

		
		// present new frame
		sdl.presentRenderer();

		Uint32 frameTime = sdl.currRealTime() - startTime;

		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
	}

	// stop the music
	Music::haltMusic();

}

