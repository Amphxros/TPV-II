#pragma once
#include <cstddef>

namespace ecs
{
using CmpIDType = std::size_t;
constexpr std::size_t maxComponents = 10;

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

};

