#include "Player.h"
#include "Environment.h"
#include "Resources.h"
#include "Tools.h"

Player* g_player = NULL;

Player::Player(int gridX, int gridY) : Sprite(gridX*TILE_SIZE -1, gridY*TILE_SIZE -3), // Place the player in terms of TILE sizes. Subtract 1 and 3 respectively for squaring correction.
									   direction(DOWN), moving(false), misalignment(0)
{
	// Initialise Fields
	sprite_sheet = Resources::GetPlayerSheet();
	max_cycles = 3 * PLAYER_WALK_CYCLE_SPEED;

	//Initialise the clips of the sprite_sheet
	int clip_w = (sprite_sheet.w / 3);
	int clip_h = (sprite_sheet.h / 4);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			SDL_Rect clip = SDL_Rect();

			clip.x = clip_w * j;
			clip.y = clip_h * i,
			
			clip.w = clip_w;
			clip.h = clip_h;

			clips[i][j] = clip;
		}
	}
}

void Player::walk(E_Direction direction)
{
	// Only allow the user the ability to move the player if the player is not already in the motion of movement
	if (!moving)
	{
		// Set the new direction
		this->direction = direction;

		// Check to see if the player can move to the front tile.
		if (GetFrontTile()->canMoveThrough) moving = true;
	}
}

GridTile* Player::GetFrontTile(void)
{
	XY frontGridPosition = GetGridPosition();
	frontGridPosition.addDirection(direction);
	
	return g_environment->getTileAt(frontGridPosition);
}

void Player::update(int delta)
{
	IncCycle();

	if (moving) // The player should keep moving in its last assigned direction 
	{
		bool moveWorld = IsAtThreshold();
		// Point to the coordinates of the object being moved
		XY* accessedCoordinates = moveWorld ? &g_environment->pos : &pos;

		int pixelsToMove;
		// Add the option to compensate the speed during slow framerates
		if (PLAYER_COMPENSATE_FOR_SLOW_FRAMERATES) pixelsToMove = PLAYER_SPEED * delta;
		else									   pixelsToMove = PLAYER_SPEED * (1000/FRAME_RATE);
		pixelsToMove *= moveWorld? -1 : 1; // Make the world move in the opposite direcion than the player
		
		// Move either this player or the world around it
		accessedCoordinates->addDirection(direction, pixelsToMove);
		// Increment the misalignment from the grid by this amount
		misalignment += pixelsToMove;

	}

	// Check to see if the player should stop
	if (abs(misalignment) >= TILE_SIZE) // The player has reached the next tile
	{
		// Reset the movement variables
		moving = false;
		misalignment = 0;

		// Snap either the player or the environment to its TILE_SIZE multiple.
		SnapPosition();
	}
}

void Player::SnapPosition(void)
{
	// Determine which to move
	bool moveWorld = IsAtThreshold();

	if (moveWorld)
	{
		g_environment->x -= ((int)g_environment->x % TILE_SIZE);
		g_environment->y -= ((int)g_environment->y % TILE_SIZE);
	}
	else
	{
		XY gp = GetGridPosition();

		pos = (gp * TILE_SIZE);

		// Correct the position, due to the inconsistency of the sprite dimensions
		pos.x -= 1;
		pos.y -= 3;

		// TODO Test to see if this works
		/*x -= 1;
		y -= 3;*/
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

	// Find the distances from the center for each threshold (all the same, different directions)
	int tilesFromCenter = PLAYER_MOVEMENT_THRESHOLD * TILE_SIZE;
	XY center = SCREEN_CENTER;
	XY centerDisplacement = center + tilesFromCenter;

	// Set the thresholds
	Directions<float> thresholds = Directions<float>(centerDisplacement);

	return (((*x <= thresholds.left)   && (direction == LEFT))   ||
			((*x >= thresholds.right)  && (direction == RIGHT))  ||
			((*y <= thresholds.top)	   && (direction == UP))	 ||
			((*y >= thresholds.bottom) && (direction == DOWN)));
}