#pragma once

// components -- forward declaration, i.e., assume they are defined somewhere
class Transform;
class Image;
#define _CMPS_LIST_  Transform,Image

// groups -- forward declaration, but they are never defined as data structures
struct Asteroid;
struct Bullet;
#define _GRPS_LIST_ Asteroid,Bullet

// handlers -- forward declaration, but they are never defined as data structures
struct Fighter;
#define _HDLRS_LIST_ Fighter

// systems -- forward declaration
class AsteroidSystem;
class BulletsSystem;
class FighterSystem;
class CollisionSystem;
class FighterGunSystem;
class RenderSystem;

#define _SYS_List_ AsteroidSystem, BulletsSystem, FighterSystem, FighterGunSystem, CollisionSystem,RenderSystem

