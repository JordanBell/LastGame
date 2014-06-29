#include "Player.h"

Player* g_player = nullptr;

void Player::E_Update(const int delta)
{
	// Update the input buffer
	if (inputBuffer > 0) inputBuffer--;

	// Check to see whether or not entities in front can be interacted with.
	if (m_newPosRecently) Compute_FrontInteractable();
	// Prompt the player, if the front can be interacted with.
	if (m_frontInteractable) Say("F", false, 5);
	else					 m_soundSource->Stop();

	Traveller::E_Update(delta);
}

void Player::Interact(void) const
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
		}
	}
}

void Player::Compute_FrontInteractable(void)
{
	// By default, there are no front interactables.
	m_frontInteractable = false;

	// Get all of the tiles in front of the player
	list<Entity*>* frontEntitiesPerLayer = GetAllFrontEntities();
	
	// For each layer
	for (int i = 0; i < 3; i++)
	{
		// Get the front entities there
		list<Entity*> layer = frontEntitiesPerLayer[i];
		
		// Check all of the front entities
		for (Entity* e : layer) {
			if ((*e)[INTERACTABLE]) 
			{
				m_frontInteractable = true;
				return;
			}
		}
	}
}


void Player::Walk(const E_Direction& direction)
{
	// Only move when the input buffer is 0
	if (inputBuffer == 0)
	{
		if (this->direction == direction) 
		{
			Traveller::Walk(direction);
			m_newPosRecently = true;
		}
		else if (!m_moving)
		{
			// If not facing that direction, just turn.
			TurnToFace(direction);
			// Wait a bit for new user response
			inputBuffer = 2;
		}
	}
}