// This file is part of the course TPV2@UCM - Samir Genaim

#include "RenderSystem.h"

#include "components/Transform.h"
#include "components/Image.h"

#include "ecs/Manager.h"

#include "sdlutils/macros.h"
#include "sdlutils/SDLUtils.h"

#include "GameManagerSystem.h"
#include "NetworkSystem.h"

RenderSystem::RenderSystem() :
		ballTr_(nullptr), //
		leftPaddelTr_(nullptr), //
		rightPaddelTr_(nullptr) {
}

RenderSystem::~RenderSystem() {
}

void RenderSystem::init()
{
}


void RenderSystem::update() {

	auto entities = manager_->getEnteties();

	for(auto e :entities){
	
		if(manager_->hasGroup<Bullet>(e)){
			auto tr_ = manager_->getComponent<Transform>(e);
			SDL_Rect dest;
			dest.x = tr_->pos_.getX();
			dest.y = tr_->pos_.getY();
			dest.w = tr_->width_;
			dest.h = tr_->height_;
			if (manager_->getComponent<Image>(e)->tex_ != nullptr) {
				manager_->getComponent<Image>(e)->tex_->render(dest, tr_->rotation_);
			}
		}
	}



	drawFighters();
	drawScore();
	drawMsgs();
	drawNames();
}

void RenderSystem::drawFighters(){
	auto fA=  manager_->getHandler<FighterA>();
	auto fB=  manager_->getHandler<FighterB>();

	auto imgA = manager_->getComponent<Image>(fA);
	auto imgB = manager_->getComponent<Image>(fB);
	
	auto tA = manager_->getComponent<Transform>(fA);
	auto tB = manager_->getComponent<Transform>(fB);
	
	SDL_Rect dest;
	dest.x = tA->pos_.getX();
	dest.y = tA->pos_.getY();
	dest.w = tA->width_;
	dest.h = tA->height_;
	
	imgA->tex_->render(dest, tA->rotation_);

	dest.x = tB->pos_.getX();
	dest.y = tB->pos_.getY();
	dest.w = tB->width_;
	dest.h = tB->height_;
	

	imgB->tex_->render(dest, tB->rotation_);

}

void RenderSystem::drawNames()
{
	auto &names_ = manager_->getSystem<NetworkSystem>()->getNames();
	
	// name of player 0
	Texture name_0(
			sdlutils().renderer(), //
			names_[0], sdlutils().fonts().at("ARIAL16"),
			build_sdlcolor(0xffffffff));
	name_0.render(10, 10);
	
	// name of player 1
	Texture name_1(
			sdlutils().renderer(), //
			names_[1], sdlutils().fonts().at("ARIAL16"),
			build_sdlcolor(0xffffffff));
	name_1.render(sdlutils().width() - name_1.width() - 10, 10);
}



void RenderSystem::drawScore() {

	auto &score_ = manager_->getSystem<GameManagerSystem>()->getScore();
	// score
	Texture scoreMsg(
			sdlutils().renderer(), //
			std::to_string(score_[0]) + " - " + std::to_string(score_[1]),
			sdlutils().fonts().at("ARIAL16"), build_sdlcolor(0xffffffff));
	scoreMsg.render((sdlutils().width() - scoreMsg.width()) / 2, 10);
}

void RenderSystem::drawMsgs() {
	auto state_ = manager_->getSystem<GameManagerSystem>()->getState();
	// message when game is not running
	if (state_ != GameManagerSystem::RUNNING) {

		// game over message
		if (state_ == GameManagerSystem::GAMEOVER) {
			auto &t = sdlutils().msgs().at("gameOver");
			t.render((sdlutils().width() - t.width()) / 2,
					(sdlutils().height() - t.height()) / 2 - 50);
		}

		// new game message
		else if (state_ == GameManagerSystem::NEWGAME) {
			auto &t = sdlutils().msgs().at("Start");
			t.render((sdlutils().width() - t.width()) / 2,
					sdlutils().height() / 2 + t.height() * 2);
		} else {
			auto &t = sdlutils().msgs().at("Continue");
			t.render((sdlutils().width() - t.width()) / 2,
					sdlutils().height() / 2 + t.height() * 2);
		}

		auto myId = manager_->getSystem<NetworkSystem>()->getId();

		// draw player side message
		Texture side(
				sdlutils().renderer(), //
				(myId == 0 ? "You are playing left" : " You are playing right"),
				sdlutils().fonts().at("ARIAL16"), build_sdlcolor(0xffffffff));
		side.render((sdlutils().width() - side.width()) / 2,
				sdlutils().height() - side.height() - 2 * side.height() - 10);

		// draw switch side message
		auto isMaster = manager_->getSystem<NetworkSystem>()->isMaster();
		auto isGameReady = manager_->getSystem<NetworkSystem>()->isGameReady();

		if (isMaster && !isGameReady) {
			Texture switch_key(
					sdlutils().renderer(), //
					"(press P to switch side)",
					sdlutils().fonts().at("ARIAL16"),
					build_sdlcolor(0xffffffff));
			switch_key.render((sdlutils().width() - switch_key.width()) / 2,
					sdlutils().height() - switch_key.height() - 10);
		}

	}
}

//void RenderSystem::drawNames() {
	//auto &names_ = manager_->getSystem<NetworkSystem>()->getNames();
	//
	//// name of player 0
	//Texture name_0(
	//		sdlutils().renderer(), //
	//		names_[0], sdlutils().fonts().at("ARIAL16"),
	//		build_sdlcolor(0xffffffff));
	//name_0.render(10, 10);
	//
	//// name of player 1
	//Texture name_1(
	//		sdlutils().renderer(), //
	//		names_[1], sdlutils().fonts().at("ARIAL16"),
	//		build_sdlcolor(0xffffffff));
	//name_1.render(sdlutils().width() - name_1.width() - 10, 10);
	//
	//// draw a star next to the master name
	//auto isMaster = manager_->getSystem<NetworkSystem>()->isMaster();
	//auto myId = manager_->getSystem<NetworkSystem>()->getId();
	//
	//Texture isMasterMsg(sdlutils().renderer(), //
	//		"*", //
	//		sdlutils().fonts().at("ARIAL24"), build_sdlcolor(0xff0000ff));
	//isMasterMsg.render(
	//		(isMaster && myId == 1) || (!isMaster && myId == 0) ?
	//				sdlutils().width() - isMasterMsg.width() - 1 : 1, 10);
//	//
//}
