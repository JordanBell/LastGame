#include "Player.h"
#include "Environment.h"
#include "Resources.h"
#include "Tools.h"

//Initialise the size and position of each sprite clip
Player::Player(float x, float y) : Sprite(x, y), direction(DOWN), moving(false), misalignment(0)
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
		/*GridTile* frontTile = GetFrontTile();
		if (frontTile->canMoveThrough)
		{
			moving = true; 
			this->direction = direction;
		}*/

		moving = true; 
		this->direction = direction;
	}
}

//GridTile* Player::GetFrontTile(void)
//{
//	XY* frontGridPosition = GetGridPosition();
//	
//	frontGridPosition->y -= (this->direction == UP);
//	frontGridPosition->y += (this->direction == DOWN);
//	frontGridPosition->x -= (this->direction == LEFT);
//	frontGridPosition->x += (this->direction == RIGHT);
//	
//	return g_environment->getTileAt(frontGridPosition);
//}
	
void Player::IncCycle(void) 
{
	cycle = (cycle >= (max_cycles-1)) ? 0 : cycle+1; 
}

void Player::update(int delta)
{
	IncCycle();

	if (moving) // The player should keep moving in its last assigned direction 
	{
		int pixelsToMove = PLAYER_SPEED*delta;
		
		misalignment += pixelsToMove;
		y -= (this->direction == UP)	* pixelsToMove;
		y += (this->direction == DOWN)	* pixelsToMove;
		x -= (this->direction == LEFT)	* pixelsToMove;
		x += (this->direction == RIGHT) * pixelsToMove;
	}
	else
	{
		//
	}

	// Check to see if the player should keep moving
	if (misalignment >= TILE_SIZE) // The player has reached the next tile
	{
		moving = false;
		misalignment = 0;
	}
}