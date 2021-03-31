#pragma once
#include <cstddef>

namespace ecs
{
	using CmpIDType = std::size_t;
	constexpr std::size_t maxComponents = 20;

	using GroupIDType = std::size_t;
	constexpr std::size_t maxGroups = 10;

	using HandlerIDType = std::size_t;
	constexpr std::size_t maxHandlers = 10;

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
		CollisionsManager,

	};

	enum GroupID : GroupIDType {
		Asteroids,
		Bullets,
		Fighter,
		Other
	};

	enum HandlerID : HandlerIDType {
		AsteroidsSys,
		BulletsSys,
		CollisionsSys,
		RenderSys,
		GMSys
	};


};

