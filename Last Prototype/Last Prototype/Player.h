#ifndef player_h
#define player_h
#include "Sprite.h"
#include <math.h>

#define SPEED 0.3 // The movement speed (independent of framerate)
#define WALK_SPEED 5 // The number of frames between cycle changes
#define STILL 1

class Player : public Sprite {
public:
	enum {
		UP,
		RIGHT,
		DOWN,
		LEFT
	} Directions;
	
	//De/Constructors
	Player(int x, int y);
	~Player() { }
	
	void move(int direction);
	void stop_moving () { moving = false; }

	void update(int delta);

protected:
	void IncCycle(void);

private:
	int direction; //The direction being faced by the player
	bool moving;
	SDL_Rect* clips[ 4 ][ 3 ]; //The 12 sprite locations in the sprite sheet

	void set_skin() { skin = (moving) ? clips[direction][cycle/WALK_SPEED] : clips[direction][STILL]; };
};

#endif