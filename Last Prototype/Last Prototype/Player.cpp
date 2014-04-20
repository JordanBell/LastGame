#include "Player.h"
#include "Environment.h"
#include "Resources.h"
#include "Tools.h"

//Initialise the size and position of each sprite clip
Player::Player(float x, float y) : Sprite(x, y), direction(DOWN), moving(false), misalignment(0), gridPosition(GetGridPosition(x, y))
{
	sprite_sheet = g_resources->GetPlayerSheet();
	max_cycles = 3 * PLAYER_WALK_CYCLE_SPEED;

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

void Player::move(int direction)
{
	// Only allow the user the ability to move the player if the player is not already in the motion of movement
	if (!moving)
	{
		this->direction = direction;
		GridTile* frontTile = GetFrontTile();

		// Check to see if it's a valid move.
		if (frontTile->canMoveThrough)
		{
			moving = true; 
		}
	}
}

GridTile* Player::GetFrontTile(void)
{
	XY* frontGridPosition = GetGridPosition();
	
	frontGridPosition->y -= (this->direction == UP);
	frontGridPosition->y += (this->direction == DOWN);
	frontGridPosition->x -= (this->direction == LEFT);
	frontGridPosition->x += (this->direction == RIGHT);
	
	return g_environment->getTileAt(frontGridPosition);
}
	
void Player::IncCycle(void) 
{
	cycle = (cycle >= (max_cycles-1)) ? 0 : cycle+1; 
}

void Player::update(int delta)
{
	IncCycle();

	if (moving) // The player should keep moving in its last assigned direction 
	{
		bool moveWorld = IsAtThreshold();
		float* cx = moveWorld ? &g_environment->x : &x;
		float* cy = moveWorld ? &g_environment->y : &y;

		int pixelsToMove;
		if (PLAYER_COMPENSATE_FOR_SLOW_FRAMERATES) pixelsToMove = PLAYER_SPEED * delta;
		else									   pixelsToMove = PLAYER_SPEED * (1000/FRAME_RATE);
		pixelsToMove *= moveWorld? -1 : 1; // Make the world move in the opposite direcion than if the player was moving
		
		misalignment += pixelsToMove;
		//printf("Misalignment:  %d\n", misalignment);
		*cy -= (this->direction == UP)	  * pixelsToMove;
		*cy += (this->direction == DOWN)  * pixelsToMove;
		*cx -= (this->direction == LEFT)  * pixelsToMove;
		*cx += (this->direction == RIGHT) * pixelsToMove;
	}

	// Check to see if the player should keep moving
	if (abs(misalignment) >= TILE_SIZE) // The player has reached the next tile
	{
		moving = false;
		misalignment = 0;

		// Change the grid position according to the direciton
		gridPosition->y -= (this->direction == UP);
		gridPosition->y += (this->direction == DOWN);
		gridPosition->x -= (this->direction == LEFT);
		gridPosition->x += (this->direction == RIGHT);

		SnapPosition();
	}
}

void Player::SnapPosition(void)
{
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
	Directions<bool> noShow  = Directions<bool>(
		(int)g_environment->y >= 0,
		(int)g_environment->y <= SCREEN_HEIGHT - WORLD_HEIGHT * TILE_SIZE,
		(int)g_environment->x >= 0,
		(int)g_environment->x <= SCREEN_WIDTH  - WORLD_WIDTH * TILE_SIZE);
	
	if ((noShow.top	   && direction == UP)	 ||
		(noShow.bottom && direction == DOWN) ||
		(noShow.left   && direction == LEFT) ||
		(noShow.right  && direction == RIGHT)) return false;



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
}