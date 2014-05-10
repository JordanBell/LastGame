#pragma once
#include "Tools.h"

// A global flag
//bool g_flag = false;

// ENVIRONMENT
const int TILE_SIZE = 32; // Note: Sprite Sheets must support the selected TILE_SIZE
const int WORLD_WIDTH  = 25; // (In terms of TILE_SIZEs)
const int WORLD_HEIGHT = 25; // (In terms of TILE_SIZEs)
const XY WORLD_DIMENSIONS = XY((WORLD_WIDTH), WORLD_HEIGHT);

// SCREEN
const XY WINDOWED_SCREEN_RES(15*TILE_SIZE, 10*TILE_SIZE);
const int SCREEN_WIDTH  = WINDOWED_SCREEN_RES.x;
const int SCREEN_HEIGHT = WINDOWED_SCREEN_RES.y;
const XY SCREEN_CENTER(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
const int SCREEN_BPP = 32;
const bool FULL_SCREEN = false;

// GAME
const int FRAME_RATE = 60;

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