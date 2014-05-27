#pragma once
#include "Tools.h"
//#include "EntityFormat.h"

/* Entity format flag. */
const Uint8 ENTITY_GRAPHIC			= 0x00;
const Uint8 ENTITY_GRIDINDEPENDENT	= 0x01;
const Uint8 ENTITY_LIGHTSOURCE		= 0x02;
const Uint8 ENTITY_TANGIBLE			= 0x04;
const Uint8 ENTITY_INTERACTABLE		= 0x08;
const Uint8 ENTITY_TRAVELLER		= 0x10;
const Uint8 ENTITY_UPDATABLE		= 0x20;
const Uint8 ENTITY_ANIMATED			= 0x30;

/* Entity format preset. */
const Uint8 CONTAINER_FRMT = ENTITY_UPDATABLE | ENTITY_GRIDINDEPENDENT;
const Uint8 TRAVELLER_FRMT = ENTITY_UPDATABLE | ENTITY_ANIMATED | ENTITY_TRAVELLER | ENTITY_INTERACTABLE | ENTITY_TANGIBLE;
const Uint8 PLAYER_FRMT	=	 ENTITY_UPDATABLE | ENTITY_ANIMATED | ENTITY_TRAVELLER;
const Uint8 DOOR_FRMT =		 ENTITY_ANIMATED  | ENTITY_INTERACTABLE | ENTITY_TANGIBLE;
const Uint8 TILE_FLOOR_FRMT= ENTITY_GRAPHIC;
const Uint8 TILE_WALL_FRMT = ENTITY_TANGIBLE;

// ENVIRONMENT
const int TILE_SIZE = 32; // Note: Sprite Sheets must support the selected TILE_SIZE
const int WORLD_WIDTH  = 100; // (In terms of TILE_SIZEs)
const int WORLD_HEIGHT = 100; // (In terms of TILE_SIZEs)
const Dimensions WORLD_DIMENSIONS((WORLD_WIDTH), WORLD_HEIGHT);

// SCREEN
const bool FULL_SCREEN_INITIAL = false;
const Dimensions WINDOWED_SCREEN_RES = (16*TILE_SIZE, 10*TILE_SIZE);
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