#include "Player.h"

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
		list<Entity*> frontEntities = GetFrontEntities();

		// Interact with them all
		for (Entity* ft : frontEntities)
			ft->OnInteract();

		//// Interact with just the top tile
		//frontEntities.front()->OnInteract();
	}
}

void Player::E_Update(const int delta)
{
	// Update the input buffer
	if (inputBuffer > 0) inputBuffer--;

	Traveller::E_Update(delta);
}