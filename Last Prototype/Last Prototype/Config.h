#pragma once
#include "Tools.h"

// SCREEN
const int SCREEN_WIDTH = 1664;
const int SCREEN_HEIGHT = 960;
const XY SCREEN_CENTER = XY(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
const int SCREEN_BPP = 32;
const bool FULL_SCREEN = true;

// GAME
const int FRAME_RATE = 60;

// PLAYER
const float PLAYER_SPEED = 0.3;			 // The player's movement speed (independent of framerate). ADVISED: Keep between 0 and 1 to prevent wall clipping.
const int	PLAYER_WALK_CYCLE_SPEED = 3; // The number of frames between the player's clip changes
const bool  PLAYER_COMPENSATE_FOR_SLOW_FRAMERATES = false;

// ENVIRONMENT
const int TILE_SIZE = 32;
const int WORLD_WIDTH  = 100; // (In terms of TILE_SIZEs)
const int WORLD_HEIGHT = 100; // (In terms of TILE_SIZEs)
const bool ONLY_MOVE_WORLD = false;
const int PLAYER_MOVEMENT_THRESHOLD = ONLY_MOVE_WORLD ? 0 : 4; // The number of tiles either side of the edge of the screen, beyond which the world is animated around instead of the player

// HOUSES
const float HOUSE_SIZE_DEVIATION = 0.2; // The percentage increase or decrease in house sizes