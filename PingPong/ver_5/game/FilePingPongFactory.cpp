// This file is part of the course TPV2@UCM - Samir Genaim

#include "FilePingPongFactory.h"

#include <array>
#include "../json/JSON.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "BounceOnBorderPC.h"
#include "Container.h"
#include "CtrlMsgRC.h"
#include "EmptyRectRC.h"
#include "FilledRectRC.h"
#include "GameCtrlIC.h"
#include "GameManager.h"
#include "ImageRC.h"
#include "PaddleAIPhysics.h"
#include "PaddleKBCtrlIC.h"
#include "PaddleMouseCtrlIC.h"
#include "PingPongRulePC.h"
#include "ScoreRC.h"
#include "SimpleMovePC.h"
#include "StopOnBorderPC.h"

FilePingPongFactory::FilePingPongFactory(std::string file) {

	// load JSON configuration file
	JSONValue *jValue = JSON::ParseFromFile(file);

	// check it was loaded correctly
	// the root must be a JSON object
	if (jValue == nullptr || !jValue->IsObject()) {
		throw "Something went wrong while load/parsing '" + file + "'";
	}

	// we know the root is JSONObject
	cfg_ = jValue->AsObject();

}

FilePingPongFactory::~FilePingPongFactory() {
}

GameObject* FilePingPongFactory::createRightPaddle(GameObject *ball) {
	Container *rightPaddle = createPaddle(cfg_["rightpaddle"], ball);

	rightPaddle->getPos().set(sdlutils().width() - 15,
			sdlutils().height() / 2 - 25);

	return rightPaddle;
}

GameObject* FilePingPongFactory::createLeftPaddle(GameObject *ball) {
	Container *leftPaddle = createPaddle(cfg_["leftpaddle"], ball);

	leftPaddle->getPos().set(10, sdlutils().height() / 2 - 25);

	return leftPaddle;
}

GameObject* FilePingPongFactory::createGameManager(GameObject *ball,
		GameObject *leftPaddle, GameObject *rightPaddle) {
	Container *gm = new GameManager(ball, leftPaddle, rightPaddle);
	gm->addComponent(new GameCtrlIC());
	gm->addComponent(new PingPongRulePC());
	gm->addComponent(new ScoreRC());
	gm->addComponent(new CtrlMsgRC());
	return gm;
}

GameObject* FilePingPongFactory::createBall() {
	Container *ball = new Container();

	JSONValue *ballcfgVal = cfg_["ball"];

	// default values
	std::string type = "rect";
	std::string color = "0xaaffeeff";
	std::string image = "tennis_ball";

	if (ballcfgVal != nullptr) {
		JSONObject ballcfgObj = ballcfgVal->AsObject();

		// type
		if (ballcfgObj["type"] != nullptr) {
			type = ballcfgObj["type"]->AsString();
		}

		// color
		if (ballcfgObj["color"] != nullptr) {
			color = ballcfgObj["color"]->AsString();
		}

		// image
		if (ballcfgObj["image"] != nullptr) {
			image = ballcfgObj["image"]->AsString();
		}
	}

	if (type == "rect") {
		ball->addComponent(new FilledRectRC(build_sdlcolor(color)));
	} else if (type == "erect") {
		ball->addComponent(new EmptyRectRC(build_sdlcolor(color)));
	} else if (type == "image") {
		ball->addComponent(new ImageRC(&sdlutils().images().at(image)));
	} else {
		throw "unknown value for 'type': " + type;
	}

	ball->addComponent(new SimpleMovePC());
	ball->addComponent(new BounceOnBorderPC());
	ball->setWidth(10.0f);
	ball->setHeight(10.0f);
	ball->getPos().set(sdlutils().width() / 2 - 5, sdlutils().height() / 2 - 5);

	return ball;
}

Container* FilePingPongFactory::createPaddle(JSONValue *jValue,
		GameObject *ball) {

	Container *paddle = new Container();

	// default values
	std::string type = "rect";
	std::string color = "0xaaffeeff";
	std::string ctrl = "mouse";
	std::array<SDL_Scancode, 3> keys = { SDL_SCANCODE_UP, SDL_SCANCODE_DOWN,
			SDL_SCANCODE_LEFT };

	if (jValue != nullptr) {
		JSONObject paddlecfgObj = jValue->AsObject();

		// type
		if (paddlecfgObj["type"] != nullptr) {
			type = paddlecfgObj["type"]->AsString();
		}

		// color
		if (paddlecfgObj["color"] != nullptr) {
			color = paddlecfgObj["color"]->AsString();
		}

		// image
		if (paddlecfgObj["ctrl"] != nullptr) {
			ctrl = paddlecfgObj["ctrl"]->AsString();
		}

		// image
		if (paddlecfgObj["keys"] != nullptr) {
			JSONArray arr = paddlecfgObj["keys"]->AsArray();
			for (int i = 0u; i < 3; i++) {
				keys[i] = (SDL_Scancode) arr[i]->AsNumber();
			}
		}
	}

	if (type == "rect") {
		paddle->addComponent(new FilledRectRC(build_sdlcolor(color)));
	} else if (type == "erect") {
		paddle->addComponent(new EmptyRectRC(build_sdlcolor(color)));
	} else {
		throw "unknown value for 'type': " + type;
	}

	if (ctrl == "keyboard") {
		auto kbIC = new PaddleKBCtrlIC();
		kbIC->setKeys(keys[0], keys[1], keys[2]);
		paddle->addComponent(kbIC);
	} else if (ctrl == "mouse") {
		paddle->addComponent(new PaddleMouseCtrlIC());
	} else if (ctrl == "auto") {
		paddle->addComponent(new PaddleAIPhysics(ball));
	} else {
		throw "unknown value for 'ctrl': " + ctrl;
	}

	paddle->addComponent(new SimpleMovePC());
	paddle->addComponent(new StopOnBorderPC());
	paddle->setWidth(10.0f);
	paddle->setHeight(50.0f);

	return paddle;
}

