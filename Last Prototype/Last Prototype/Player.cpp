#include "Player.h"
#include "Environment.h"
#include "Resources.h"
#include "Tools.h"
#include "Camera.h"

Player* g_player = NULL;

<<<<<<< HEAD
Player::Player(int gridX, int gridY) : Sprite(gridX*TILE_SIZE, gridY*TILE_SIZE), // Place the player in terms of TILE sizes. Subtract 1 and 3 respectively for squaring correction.
									   direction(DOWN), moving(false), misalignment(0)
{
	// Initialise Fields
	sprite_sheet = Resources::GetPlayerSheet();
	
	// It's 	 4 *, because the walk cycle reuses the still sprite as an inbetween
	max_cycles = 4 * PLAYER_WALK_CYCLE_SPEED;
=======
//Initialise the size and position of each sprite clip
Player::Player(int x, int y) : Sprite(x*TILE_SIZE -1, y*TILE_SIZE -3), // Place the player in terms of TILE sizes. Subtract 1 and 3 respectively for squaring correction
								   direction(DOWN), moving(false), misalignment(0), gridPosition(GetGridPosition(x, y))
{
	sprite_sheet = g_resources->GetPlayerSheet();
	max_cycles = 3 * PLAYER_WALK_CYCLE_SPEED;
>>>>>>> parent of f6a1270... Oh wait, no. Conversion Complete

	//Initialise the clips of the sprite_sheet
	int clip_w = (sprite_sheet->w / 3);
	int clip_h = (sprite_sheet->h / 4);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			SDL_Rect* clip = new SDL_Rect();

			clip->x = clip_w * j;
			clip->y = clip_h * i,
			
			clip->w = clip_w;
			clip->h = clip_h;

			clips[i][j] = clip;
		}
	}
}

<<<<<<< HEAD
void Player::walk(const E_Direction& direction)
=======
void Player::move(int direction)
>>>>>>> parent of f6a1270... Oh wait, no. Conversion Complete
{
	// Only allow the user the ability to move the player if the player is not already in the motion of movement
	if (!moving)
	{
		this->direction = direction;
		GridTile* frontTile = GetFrontTile();

<<<<<<< HEAD
		// Check to see if the player can move to the front tile.
		moving = CanMoveForward();
=======
		// Check to see if it's a valid move.
		if (frontTile->canMoveThrough)
		{
			moving = true; 
		}
>>>>>>> parent of f6a1270... Oh wait, no. Conversion Complete
	}
}

bool Player::CanMoveForward() const
{
<<<<<<< HEAD
	// The player can move forward if none of the tiles in front of them are solid

	list<GridTile*> frontTiles;
=======
	XY* frontGridPosition = GetGridPosition();
	
	frontGridPosition->y -= (this->direction == UP);
	frontGridPosition->y += (this->direction == DOWN);
	frontGridPosition->x -= (this->direction == LEFT);
	frontGridPosition->x += (this->direction == RIGHT);
>>>>>>> parent of f6a1270... Oh wait, no. Conversion Complete
	
	// Check the bottom layer
	frontTiles = GetFrontTiles(false);
	for (GridTile* ft : frontTiles)
		if (!ft->canMoveThrough) return false;

	// Check the top layer
	frontTiles = GetFrontTiles(true);
	for (GridTile* ft : frontTiles)
		if (!ft->canMoveThrough) return false;

	return true;
}

void Player::interact() const
{
	if (!moving)
	{
		// Get all of the tiles in front of the player
		list<GridTile*> frontTiles = GetFrontTiles();

		// Interact with them all
		for (GridTile* ft : frontTiles)
			ft->onInteract();

		//// Interact with just the top
		//frontTiles.front()->onInteract();
	}
}
	
void Player::IncCycle(void) 
{
	cycle = (cycle >= (max_cycles-1)) ? 0 : cycle+1; 
}

list<GridTile*>& Player::GetFrontTiles(bool top) const
{
	XY& frontGridPosition = GetGridPosition();

	// Find the gridPosition in front of the direction the player is facing
	frontGridPosition.addDirection(direction);
	
	return g_environment->GetTilesAt(frontGridPosition, top);
}

void Player::update(const int delta)
{
	if (moving) // The player should keep moving in its last assigned direction 
	{
<<<<<<< HEAD
		IncCycle();
=======
		bool moveWorld = IsAtThreshold();
		float* cx = moveWorld ? &g_environment->x : &x;
		float* cy = moveWorld ? &g_environment->y : &y;

>>>>>>> parent of f6a1270... Oh wait, no. Conversion Complete
		int pixelsToMove;
		if (PLAYER_COMPENSATE_FOR_SLOW_FRAMERATES) pixelsToMove = PLAYER_SPEED * delta;
		else									   pixelsToMove = PLAYER_SPEED * (1000/FRAME_RATE);
		
<<<<<<< HEAD
		// Move the player by this amount
		pos.addDirection(direction, pixelsToMove);

		// Increment the misalignment from the grid by this amount
		misalignment += pixelsToMove;
=======
		misalignment += pixelsToMove;
		//printf("Misalignment:  %d\n", misalignment);
		*cy -= (this->direction == UP)	  * pixelsToMove;
		*cy += (this->direction == DOWN)  * pixelsToMove;
		*cx -= (this->direction == LEFT)  * pixelsToMove;
		*cx += (this->direction == RIGHT) * pixelsToMove;
>>>>>>> parent of f6a1270... Oh wait, no. Conversion Complete
	}

	// Check to see if the player should keep moving
	if (abs(misalignment) >= TILE_SIZE) // The player has reached the next tile
	{
		moving = false;
		misalignment = 0;

<<<<<<< HEAD
		// Snap the player to a TILE_SIZE multiple.
=======
		// Change the grid position according to the direciton
		gridPosition->y -= (this->direction == UP);
		gridPosition->y += (this->direction == DOWN);
		gridPosition->x -= (this->direction == LEFT);
		gridPosition->x += (this->direction == RIGHT);

>>>>>>> parent of f6a1270... Oh wait, no. Conversion Complete
		SnapPosition();
	}
}

void Player::SnapPosition(void)
{
<<<<<<< HEAD
	// Round down this position to the nearest grid position TILE_SIZE multiple
	pos = GetGridPosition() * TILE_SIZE;
}

void Player::set_skin(void)
{ 
	int cycleIndex = cycle/PLAYER_WALK_CYCLE_SPEED;
	if (cycleIndex == 3) cycleIndex = 1; // If at the fourth part of the cycle, set the index at 1 (in between forward and back)

	// Set the skin based on the index
	skin = (moving) ? 
			clips[direction][cycleIndex] : 
			clips[direction][STILL]; 
=======
	bool moveWorld = IsAtThreshold();
	float* cx = moveWorld ? &g_environment->x : &x;
	float* cy = moveWorld ? &g_environment->y : &y;

	if (IsAtThreshold())
	{
		g_environment->x -= ((int)g_environment->x % TILE_SIZE);
		g_environment->y -= ((int)g_environment->y % TILE_SIZE);
	}
	else
	{
		XY gp = *GetGridPosition();

		x = g_environment->x + (gp.x * TILE_SIZE) - 1;
		y = g_environment->y + (gp.y * TILE_SIZE) - 3;
	}
}

bool Player::IsAtThreshold(void)
{
	// Do not move the camera if the map is at the edge - we don't want to show unrendered areas. It's glitch city in there!
	Directions<bool> noShows = g_environment->GetEdgeBools();
		
	if ((noShows.top	&& direction == UP)	  ||
		(noShows.bottom && direction == DOWN) ||
		(noShows.left   && direction == LEFT) ||
		(noShows.right  && direction == RIGHT)) return false;

	// Set the thresholds
	Directions<float> thresholds = Directions<float>(
		SCREEN_CENTER.y - PLAYER_MOVEMENT_THRESHOLD * TILE_SIZE,
		SCREEN_CENTER.y + PLAYER_MOVEMENT_THRESHOLD * TILE_SIZE,
		SCREEN_CENTER.x - PLAYER_MOVEMENT_THRESHOLD * TILE_SIZE, 
		SCREEN_CENTER.x + PLAYER_MOVEMENT_THRESHOLD * TILE_SIZE);

	return (((x <= thresholds.left)   && (direction == LEFT))   ||
			((x >= thresholds.right)  && (direction == RIGHT))  ||
			((y <= thresholds.top)	  && (direction == UP))	    ||
			((y >= thresholds.bottom) && (direction == DOWN)));
>>>>>>> parent of f6a1270... Oh wait, no. Conversion Complete
}