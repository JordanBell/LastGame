#ifndef player_h
#define player_h

#include <math.h>
#include "Config.h"

#include "Sprite.h"
#include "GridTiles.h"

#define STILL 1 // The index at which the player's sprite is still, not in the walk cycle.

class Player : public Sprite {
public:	
	Player(int x, int y);
	~Player() {}
	
	// Update the player's data
	void update(int delta);



	// Move the player, or the world, based on the player's movement.
	void walk(E_Direction direction);
	
	// Interact with the object in front of the player
	void interact();

	// Snap the player to the grid, or the grid to a TILE_SIZE multiple coordinate.
	void SnapPosition(void);



private:
	int misalignment; // The tracked difference between the player and their last TILE-aligned position.
	E_Direction direction; //The direction being faced by the player.
	bool moving; // Whether or not the player is moving.
	SDL_Rect clips[ 4 ][ 3 ]; //The 12 sprite locations in the sprite sheet: [direction] by [cycle].



	// Get the GridTile object in front of the player's position
	GridTile* GetFrontTile(void);

	// Set the skin (sprite) for this object, based on its direction and progress through the walk cycle.
	void set_skin(void) { skin = (moving) ? clips[direction][cycle/PLAYER_WALK_CYCLE_SPEED] : clips[direction][STILL]; }

	// Return whether or not the player is at the movement threshold, at which the environment is animated rather than the player
	bool IsAtThreshold(void);
};

// A global player object
extern Player* g_player;

#endif