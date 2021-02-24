// This file is part of the course TPV2@UCM - Samir Genaim

#include "ScoreRC.h"

#include <string>
#include "../sdlutils/SDLUtils.h"
#include "Container.h"
#include "GameManager.h"

using std::__1::to_string;

ScoreRC::ScoreRC() {
}

ScoreRC::~ScoreRC() {
}

void ScoreRC::render(Container *c) {
	auto gm = static_cast<GameManager*>(c);
	auto &score = gm->getScore();

	// score
	Texture scoreMsg(
			sdlutils().renderer(), //
			std::to_string(score[0]) + " - " + std::to_string(score[1]),
			sdlutils().fonts().at("ARIAL16"), build_sdlcolor(0xffffffff));
	scoreMsg.render((sdlutils().width() - scoreMsg.width()) / 2, 10);

}
