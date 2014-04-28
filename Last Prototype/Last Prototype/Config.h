#pragma once
#include "Tools.h"

// ENVIRONMENT
const int TILE_SIZE = 32;
const int WORLD_WIDTH  = 38; // (In terms of TILE_SIZEs)
const int WORLD_HEIGHT = 38; // (In terms of TILE_SIZEs)
const XY WORLD_DIMENSIONS = XY((WORLD_WIDTH), WORLD_HEIGHT);
const bool ONLY_MOVE_WORLD = true;
const int PLAYER_MOVEMENT_THRESHOLD = ONLY_MOVE_WORLD ? 0 : 4; // The number of tiles either side of the edge of the screen, beyond which the world is animated around instead of the player

// SCREEN
const int SCREEN_WIDTH  = 24*TILE_SIZE;
const int SCREEN_HEIGHT = 20*TILE_SIZE;
//const int SCREEN_WIDTH  = WORLD_WIDTH*TILE_SIZE;
//const int SCREEN_HEIGHT = WORLD_HEIGHT*TILE_SIZE;
const XY SCREEN_CENTER = XY(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
const int SCREEN_BPP = 32;
const bool FULL_SCREEN = false;

// GAME
const int FRAME_RATE = 60;

// PLAYER
const float PLAYER_SPEED = 0.3;			 // The player's movement speed (independent of framerate). ADVISED: Keep between 0 and 1 to prevent wall clipping.
const int	PLAYER_WALK_CYCLE_SPEED = 3; // The number of frames between the player's clip changes
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