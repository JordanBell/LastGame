#include "Player.h"
#include "Environment.h"
#include "Resources.h"
#include "Tools.h"
#include "Camera.h"

Player* g_player = NULL;

void Player::MovePlayer(const E_Direction& direction)
{
	// Only move when the input buffer is 0
	if (inputBuffer == 0)
	{
		if (this->direction == direction) Walk(direction);
		else
		{
			// If not facing that direction, just turn.
			TurnToFace(direction);
			// Wait a bit for new user response
			inputBuffer = 2;
		}
	}
}

void Player::interact() const
{
	if (!m_moving)
	{
		// Get all of the tiles in front of the player
		list<TileEntity*> frontTiles = GetFrontTiles();

		// Interact with them all
		for (TileEntity* ft : frontTiles)
			ft->onInteract();

		//// Interact with just the top tile
		//frontTiles.front()->onInteract();
	}
}

void Player::E_Update(const int delta)
{
	// Update the input buffer
	if (inputBuffer > 0) inputBuffer--;

	Traveller::E_Update(delta);
}