// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

// components -- forward declaration, i.e., assume they are defined somewhere
struct Transform;
struct Image;
struct FighterCtrl;

#define _CMPS_LIST_  \
	Transform,\
	Image,\
	FighterCtrl

// groups
struct Bullet;
#define _GRPS_LIST_ Bullet

// handlers
struct FighterA;
struct FighterB;
#define _HDLRS_LIST_ \
	FighterA, \
	FighterB

// systems
class BulletsSystem;
class FighterSystem;
//class GameCtrlSystem;
class NetworkSystem;
class CollisionSystem;
class RenderSystem;
class GameManagerSystem;

#define _SYS_LIST_ \
		BulletsSystem, \
		RenderSystem, \
		FighterSystem, \
		CollisionSystem, \
		NetworkSystem, \
		GameManagerSystem
	//	GameCtrlSystem,\
