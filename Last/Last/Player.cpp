#include "Player.h"

Player* g_player = nullptr;

void Player::E_Update(const int delta)
{
	// Update the input buffer
	if (inputBuffer > 0) inputBuffer--;
	
	Traveller::E_Update(delta);
}

void Player::Interact() const
{
	if (!m_moving)
	{
		// Get all of the tiles in front of the player
		list<Entity*>* frontEntitiesPerLayer = GetAllFrontEntities();
	
		// For each layer
		for (int i = 0; i < 3; i++)
		{
			// Get the front entities there
			list<Entity*> layer = frontEntitiesPerLayer[i];
		
			// Check all of the front entities
			for (Entity* e : layer) {
				e->OnInteract();
			}

			//// Or, interact with just the top tile
			//layer.front()->OnInteract();
		}
	}
}

void Player::Walk(const E_Direction& direction)
{
	// Only move when the input buffer is 0
	if (inputBuffer == 0)
	{
		if (this->direction == direction) Traveller::Walk(direction);
		else if (!m_moving)
		{
			// If not facing that direction, just turn.
			TurnToFace(direction);
			// Wait a bit for new user response
			inputBuffer = 2;
		}
	}
}