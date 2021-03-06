#include "Player.h"
#include "Environment.h"
#include "Resources.h"
#include "Tools.h"
#include "Camera.h"

Player* g_player = NULL;

Player::Player(int x, int y) : Sprite(x*TILE_SIZE, x*TILE_SIZE), // Place the player in terms of TILE sizes.
							   direction(DOWN), moving(false), misalignment(0), inputBuffer(0)
{
	// Initialise Fields
	sprite_sheet = Resources::GetPlayerSheet();
	blitOffset = XY(0, -TILE_SIZE/2);
	
	// It's 4 *, because the walk cycle reuses the still sprite as an inbetween
	max_cycles = 4 * PLAYER_WALK_CYCLE_SPEED;

	//Initialise the clips of the sprite_sheet
	int clip_w = (sprite_sheet->w / 3);
	int clip_h = (sprite_sheet->h / 4);

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

void Player::walk(const E_Direction& direction)
{
	// Only move when the input buffer is 0
	if (inputBuffer == 0)
	{
		// Only allow the user the ability to move the player if the player is not already in the motion of movement
		if (!moving)
		{		
			// If not facing the direction of movement, turn that direction
			if (this->direction != direction) {
				TurnToFace(direction);
				return;
			}

			// Set the new direction
			this->direction = direction;

			// Check to see if the player can move to the front tile.
			moving = CanMoveForward();
		}
	}
}

void Player::TurnToFace(const E_Direction& direction)
{
	// Set the new direction
	this->direction = direction;

	inputBuffer = 2;
}

bool Player::CanMoveForward() const
{
	// The player can move forward if none of the tiles in front of them are solid

	list<TileEntity*> frontTiles;
	
	// Check the bottom layer
	frontTiles = GetFrontTiles(false);
	for (TileEntity* ft : frontTiles) {
		if (!ft->canMoveThrough) return false;
	}

	// Check the top layer
	frontTiles = GetFrontTiles(true);
	for (TileEntity* ft : frontTiles) {
		if (!ft->canMoveThrough) return false;
	}

	return true;
}

void Player::interact() const
{
	if (!moving)
	{
		// Get all of the tiles in front of the player
		list<TileEntity*> frontTiles = GetFrontTiles();

		// Interact with them all
		for (TileEntity* ft : frontTiles)
			ft->onInteract();

		//// Interact with just the top
		//frontTiles.front()->onInteract();
	}
}

list<TileEntity*>& Player::GetFrontTiles(bool top) const
{
	XY& frontGridPosition = GetGridPosition();

	// Find the gridPosition in front of the direction the player is facing
	frontGridPosition.addDirection(direction);
	
	return g_environment->GetTilesAt(frontGridPosition, top);
}

void Player::update(const int delta)
{
	// Update the input buffer
	if (inputBuffer > 0) inputBuffer--;

	if (moving) // The player should keep moving in its last assigned direction 
	{
		IncCycle();
		int pixelsToMove;
		// Add the option to compensate the speed during slow framerates
		if (PLAYER_COMPENSATE_FOR_SLOW_FRAMERATES) pixelsToMove = PLAYER_SPEED * delta;
		else									   pixelsToMove = PLAYER_SPEED * (1000/FRAME_RATE);
		
		// Move the player by this amount
		pos.addDirection(direction, pixelsToMove);

		// Increment the misalignment from the grid by this amount
		misalignment += pixelsToMove;
	}

	// Check to see if the player should stop
	if (abs(misalignment) >= TILE_SIZE) // The player has reached the next tile
	{
		// Reset the movement variables
		moving = false;
		misalignment = 0;

		// Snap the player to a TILE_SIZE multiple.
		SnapPosition();
	}
}

void Player::SnapPosition(void)
{
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
}