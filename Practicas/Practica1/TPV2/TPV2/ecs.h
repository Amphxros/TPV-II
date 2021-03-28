#pragma once
#include <cstddef>

namespace ecs
{
	using CmpIDType = std::size_t;
	constexpr std::size_t maxComponents = 20;

	using GroupIDType = std::size_t;
	constexpr std::size_t maxGroups = 10;

	using SystemIDType = std::size_t;
	constexpr std::size_t maxSystem = 10;

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
		Follow, // 2 transform, uno al que seguir (target) y otro para moverse

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

	enum SystemID : SystemIDType {
		AsteroidsSys,
		BulletsSys,
		CollisionsSys,
		RenderSys,
		GMSys
	};


};

