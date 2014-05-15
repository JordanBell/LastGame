#ifndef player_h
#define player_h

#include "Sprite.h"
#include <math.h>
#include "Config.h"
<<<<<<< HEAD
#include "Sprite.h"
=======
>>>>>>> parent of f6a1270... Oh wait, no. Conversion Complete
#include "GridTiles.h"

#define STILL 1

using namespace std;

class Player : public Sprite {
public:
	enum {
		UP,
		RIGHT,
		DOWN,
		LEFT
	} directions;
	
	Player(int x, int y);
	~Player() { }
	
<<<<<<< HEAD
	// Update the player's data
	void update(const int delta);

	// Move the player, or the world, based on the player's movement.
	void walk(const E_Direction& direction);
	
	// Interact with the object in front of the player
	void interact() const;

	// Snap the player to the grid, or the grid to a TILE_SIZE multiple coordinate.
	void SnapPosition(void);

	// Return the player's direction
	E_Direction& getDirection(void) { return direction; }



private:
	int misalignment; // The tracked difference between the player and their last TILE-aligned position.
	E_Direction direction; //The direction being faced by the player.
	bool moving; // Whether or not the player is moving.
	SDL_Rect clips[ 4 ][ 3 ]; //The 12 sprite locations in the sprite sheet: [direction] by [cycle].
	
	// Return whether or not the player can move forward
	bool CanMoveForward(void) const;

	// Get the GridTile object in front of the player's position
	list<GridTile*>& GetFrontTiles(bool top = false) const;

	// Set the skin (sprite) for this object, based on its direction and progress through the walk cycle.
	void set_skin(void);
=======
	void move(int direction);
	void update(int delta);

	void SnapPosition(void);

protected:
	void IncCycle(void);

private:
	int grid_X, grid_Y;
	XY* gridPosition;
	int misalignment;
	int direction; //The direction being faced by the player
	bool moving;
	SDL_Rect* clips[ 4 ][ 3 ]; //The 12 sprite locations in the sprite sheet

	GridTile* GetFrontTile(void);
	void set_skin() { skin = (moving) ? clips[direction][cycle/PLAYER_WALK_CYCLE_SPEED] : clips[direction][STILL]; };
	bool IsAtThreshold(void);
>>>>>>> parent of f6a1270... Oh wait, no. Conversion Complete
};

extern Player* g_player;

#endif