// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

// components -- forward declaration, i.e., assume they are defined somewhere
struct Transform;
struct Image;
struct FighterCtrl;
struct DisableAtExit;
struct FighterCtrl;

#define _CMPS_LIST_  \
	Transform,\
	Image,\
	DisableAtExit,\
	FighterCtrl,\

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
class FighterSystem;
class BulletSystem;
class GameCtrlSystem;
class NetworkSystem;
class CollisionSystem;
class RenderSystem;

class BallSystem;
class PaddlesSystem;
class GameManagerSystem;

#define _SYS_LIST_ \
		FighterSystem, \
		BulletSystem, \
		RenderSystem, \
		CollisionSystem, \
		GameCtrlSystem,\
		NetworkSystem
