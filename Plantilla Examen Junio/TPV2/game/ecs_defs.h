// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

// components -- forward declaration, i.e., assume they are defined somewhere
struct Transform;
struct Image;

#define _CMPS_LIST_  \
	Transform,\
	Image

// groups
struct Ghosts;
struct Food;
#define _GRPS_LIST_ \
	Ghosts, \
	Food

// handlers
struct PacMan;
#define _HDLRS_LIST_ \
	PacMan

// systems
class PacManSystem;
class GhostsSystem;
class FoodSystem;
class CollisionSystem;
class GameManagerSystem;
class SoundSystem;
class RenderSystem;
#define _SYS_LIST_ \
		PacManSystem, \
		GhostsSystem, \
		FoodSystem, \
		CollisionSystem, \
		GameManagerSystem, \
		SoundSystem, \
		RenderSystem

// messages
#include "messages.h"
