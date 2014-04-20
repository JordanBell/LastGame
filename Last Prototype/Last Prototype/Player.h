#ifndef player_h
#define player_h
#include "Sprite.h"
#include <math.h>
#include "Config.h"
#include "GridTiles.h"

#define STILL 1

class Player : public Sprite {
public:
	enum {
		UP,
		RIGHT,
		DOWN,
		LEFT
	} directions;
	
	//De/Constructors
	Player(float x, float y);
	~Player() { }
	
	void move(int direction);

	void update(int delta);

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
	void SnapPosition(void);
	bool IsAtThreshold(void);
};

#endif