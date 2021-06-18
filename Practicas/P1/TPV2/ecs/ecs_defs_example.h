// This file is part of the course TPV2@UCM - Samir Genaim

// DO NOT USE/MODIFY THIS FILE, IT IS JUST AN EXAMPLE OF HOW YOUR
// ecs_defs.h should look like

#pragma once

// components -- forward declaration, i.e., assume they are defined somewhere
class Transform;
class Image;
#define _CMPS_LIST_  Transform,Image

// groups -- forward declaration, but they are never defined as data structures
struct Asteroids;
struct Bullets;
#define _GRPS_LIST_  Asteroids,Bullets

// handlers -- forward declaration, but they are never defined as data structures
struct Fighter;
#define _HDLRS_LIST_ Fighter

