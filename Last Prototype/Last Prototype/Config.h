#pragma once

// SCREEN
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

// GAME
const int FRAME_RATE = 60;

// PLAYER
const float PLAYER_SPEED = 0.3;			 // The player's movement speed (independent of framerate). ADVISED: Keep between 0 and 1 to prevent wall clipping.
const int	PLAYER_WALK_CYCLE_SPEED = 3; // The number of frames between the player's clip changes
const bool  PLAYER_COMPENSATE_FOR_SLOW_FRAMERATES = false;

// ENVIRONEMENT
const int TILE_SIZE = 32;
const int WORLD_WIDTH  = 100; // (In terms of TILE_SIZEs)
const int WORLD_HEIGHT = 100; // (In terms of TILE_SIZEs)
const bool ONLY_MOVE_WORLD = true;
const int PLAYER_MOVEMENT_THRESHOLD = ONLY_MOVE_WORLD ? ((SCREEN_HEIGHT / TILE_SIZE) / 2) : 6; // The number of tiles either side of the edge of the screen, beyond which the world is animated around instead of the player