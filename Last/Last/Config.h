#pragma once
#include "Tools.h"
#include "EntityFormat.h"

// ENTITY FORMATS                    ANIMTD UPDTES TRAVLS INTRCT TNGBL LGHTSRC GRD_INDPNDNT
const EntityFormat CONTAINER_FRMT	(false, true,  false, false, false, false, true);
const EntityFormat TRAVELLER_FRMT	(true,  true,  true,  true,  true,  false, false);
const EntityFormat PLAYER_FRMT		(true,  true,  true,  false, false, false, false);
const EntityFormat DOOR_FRMT		(true,  false, false, true,  true,  false, false);
const EntityFormat TILE_FLOOR_FRMT	(false, false, false, false, false, false, false);
const EntityFormat TILE_WALL_FRMT	(false, false, false, false, true,  false, false);

// ENVIRONMENT
const int TILE_SIZE = 32; // Note: Sprite Sheets must support the selected TILE_SIZE
const int WORLD_WIDTH  = 100; // (In terms of TILE_SIZEs)
const int WORLD_HEIGHT = 100; // (In terms of TILE_SIZEs)
const Dimensions WORLD_DIMENSIONS((WORLD_WIDTH), WORLD_HEIGHT);

// SCREEN
const bool FULL_SCREEN_INITIAL = true;
const Dimensions WINDOWED_SCREEN_RES(16*TILE_SIZE, 10*TILE_SIZE);
const Dimensions HARD_MONITOR_RES(1680, 1050);

// GAME
const int FRAME_RATE = 30;
const float TRAVELLER_SPEED = 0.15;		 // Default traveller speed. ADVISED: Keep between 0 and 1 to prevent wall clipping.

// PLAYER
const float PLAYER_SPEED = 0.15;		 // The player's movement speed (independent of framerate). ADVISED: Keep between 0 and 1 to prevent wall clipping.
const int	PLAYER_WALK_CYCLE_SPEED = 4; // The number of frames between the player's clip changes
const bool  PLAYER_COMPENSATE_FOR_SLOW_FRAMERATES = false;
const bool	LIMIT_RENDER_BY_SIGHT = false;
const int	SIGHT_DISTANCE = 4;

// HOUSES
const float HOUSE_SIZE_DEVIATION = 0.2f; // The percentage variation in house sizes

//#if SDL_BYTEORDER == SDL_BIG_ENDIAN
//    rmask = 0xff000000;
//    gmask = 0x00ff0000;
//    bmask = 0x0000ff00;
//    amask = 0x000000ff;
//#else
//    rmask = 0x000000ff;
//    gmask = 0x0000ff00;
//    bmask = 0x00ff0000;
//    amask = 0xff000000;
//#endif