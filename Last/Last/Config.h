#pragma once
#include "Tools.h"

/* Entity format flags. */
const Uint8 ENTITY_GRAPHIC			= 0;
const Uint8 ENTITY_GRIDINDEPENDENT	= 1;
const Uint8 ENTITY_LIGHTSOURCE		= 2;
const Uint8 ENTITY_TANGIBLE			= 4;
const Uint8 ENTITY_INTERACTABLE		= 8;
const Uint8 ENTITY_TRAVELLER		= 16;
const Uint8 ENTITY_UPDATABLE		= 32;
const Uint8 ENTITY_ANIMATED			= 64;

/* Entity format presets. */
const Uint8 CONTAINER_FRMT = ENTITY_UPDATABLE | ENTITY_GRIDINDEPENDENT;
const Uint8 TRAVELLER_FRMT = ENTITY_UPDATABLE | ENTITY_ANIMATED | ENTITY_TRAVELLER | ENTITY_INTERACTABLE/* | ENTITY_TANGIBLE*/;
const Uint8 PLAYER_FRMT	=	 ENTITY_UPDATABLE | ENTITY_ANIMATED | ENTITY_TRAVELLER/* | ENTITY_TANGIBLE*/;
const Uint8 DOOR_FRMT =		 ENTITY_ANIMATED  | ENTITY_INTERACTABLE | ENTITY_TANGIBLE;
const Uint8 TILE_FLOOR_FRMT= ENTITY_GRAPHIC;
const Uint8 TILE_WALL_FRMT = ENTITY_TANGIBLE;
const Uint8 UI_STATUS_FRMT = ENTITY_GRIDINDEPENDENT | ENTITY_UPDATABLE/* | ENTITY_ANIMATED*/;
const Uint8 BUTTON_FRMT	   = ENTITY_GRIDINDEPENDENT | ENTITY_UPDATABLE;
const Uint8 TEXT_FRMT	   = ENTITY_GRIDINDEPENDENT;

// ENVIRONMENT
const int TILE_SIZE = 32; // Note: Sprite Sheets must support the selected TILE_SIZE
const int WORLD_WIDTH  = 100; // (In terms of TILE_SIZEs)
const int WORLD_HEIGHT = 100; // (In terms of TILE_SIZEs)
const Dimensions WORLD_DIMENSIONS(WORLD_WIDTH, WORLD_HEIGHT);

// SCREEN
const bool FULL_SCREEN_INITIAL = false;
const Dimensions LOGICAL_SIZE = Dimensions(15*TILE_SIZE, 10*TILE_SIZE);

// GAME
const int FRAME_RATE = 30;
const float TRAVELLER_SPEED = 0.10;// Default traveller speed. ADVISED: Keep between 0 and 1 to prevent wall clipping.

// PLAYER
const float PLAYER_SPEED = 0.10;		 // The player's movement speed (independent of framerate). ADVISED: Keep between 0 and 1 to prevent wall clipping.
const bool  PLAYER_COMPENSATE_FOR_SLOW_FRAMERATES = false;

// HOUSES
const float HOUSE_SIZE_DEVIATION = 0.2f; // The percentage variation in house sizes

// Testing / Debugging
const bool ENABLE_SPEECH_BUBBLES = false; // If true, begin debugging for speech bubble functionality.
const bool THROW_ERROR_ON_BAD_CLIP = false; // If true, throw an error if a clip is being set to an image that is out of its range.
const bool THROW_ERROR_ON_CUTOFF = false; // If an image is being cut off when rendering to its texture target, throw an error if true.
const bool SUPPRESS_CUTOFF_WARNING = true; // If true, print a message if not throwing an error for the above.
const bool INSTANT_START = true;
const bool MANUAL_ZOOM = true;