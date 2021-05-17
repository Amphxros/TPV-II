#pragma once
#include <cstddef>

namespace ecs
{
	using CmpIDType = std::size_t;
	constexpr std::size_t maxComponents = 25;

	using GroupIDType = std::size_t;
	constexpr std::size_t maxGroups = 10;

	using HandlerIDType = std::size_t;
	constexpr std::size_t maxHandlers = 4;

	using SystemIDType = std::size_t;
	constexpr std::size_t maxSystems = 20;
	// component id
	enum CmpID : CmpIDType {
		//caza
		Transform,
		DeAcceleration,
		Image,
		Health,
		FighterCtrl,
		Gun,
		ShowAtOppositeSide,

		//asteroide

		//transform,
		FramedImage,
		Generations,
		Follow,

		//bala
		DisableOnExit,

		//gameManager
		State,
		GameCtrl,
		AsteroidsManager,
		CollisionsManager

	};

	//groups
	enum GroupID : GroupIDType {
		AsteroidsGroup,
		BulletsGroup,
		Fighter,
		Other
	};

	enum HandlerID : HandlerIDType {
		AsteroidsHndlr,
		BulletsHndlr,
		FighterAHndlr,
		FighterBHndlr,
	};

	enum SystemID: SystemIDType {
		AsteroidSys,
		BulletSys,
		CollisionSys,
		GameCtrlSys,
		FighterSys,
		FighterGunSys,
		RenderSys,
		NetWorkSys,
	};

};

