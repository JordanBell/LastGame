#include "Traveller.h"
#include "TravellerAnimation.h"
#include "Environment.h"
Traveller::Traveller(const Coordinates& _pos) : Entity(_pos, Coordinates(0, -TILE_SIZE/2), SSID_PLAYER, TRAVELLER_FRMT, nullptr, new TravellerAnimation()), 
									   direction(DOWN),
									   m_moving(false),
									   misalignment(0),
									   m_speed(TRAVELLER_SPEED) 
{
	if (!m_format[TRAVELS]) throw ModuleMisuseException("An entity cannot inherit from Traveller if its format does not allow travelling.");
}

void Traveller::E_Update(const int delta)
{
	if (m_moving) // The traveller should keep moving in its currently assigned direction 
	{
		int pixelsToMove = m_speed * (1000/FRAME_RATE);
		
		// Move by this amount
		pos.addDirection(direction, pixelsToMove);

		// Increment the misalignment from the grid by this amount
		if (!m_format[GRID_INDEPENDENT]) misalignment += pixelsToMove;
	}

	// Check to see if the traveller should stop
	if (m_format[GRID_INDEPENDENT]) m_moving = false; // No need to check to see if at TILE_SIZE multiple if Grid Independent
	else
	{
		if (abs(misalignment) >= TILE_SIZE) // The traveller has reached the next tile
		{
			// Reset the movement variables
			m_moving = false;
			misalignment = 0;

			// Snap the traveller to a TILE_SIZE multiple.
			SnapPosition();
		}
	}
}

void Traveller::Walk(const E_Direction& direction)
{
	// Only move if is not already in the motion of movement
	if (!m_moving)
	{		
		// Set the new direction
		TurnToFace(direction);

		// If the traveller can move to the next tile, set movement as true
		if (CanMoveForward()) m_moving = true;
	}
}

void Traveller::TurnToFace(const E_Direction& direction)
{
	// Set the new direction
	this->direction = direction;
}

void Traveller::SnapPosition(void)
{
	// Round down this position to the nearest grid position TILE_SIZE multiple
	pos = GetGridPosition() * TILE_SIZE;
}

bool Traveller::CanMoveForward() const
{
	// The traveller can move forward if none of the Entities in front of them are Tangible
	list<Entity*>* frontEntitiesPerLayer = GetAllFrontEntities();
	
	// For each layer
	for (int layerIndex = BOTTOM_LAYER; layerIndex < TOP_LAYER; layerIndex++)
	{
		// Get the front entities there
		list<Entity*> layer = frontEntitiesPerLayer[layerIndex];
		
		// Check all of the front entities
		for (Entity* ft : layer) {
			if (!ft->CanMoveThrough()) return false;
		}
	}

	return true;
}

list<Entity*>& Traveller::GetFrontEntities(Layer layer) const
{
	Coordinates& frontGridPosition = GetGridPosition();

	// Find the gridPosition in front of the direction the traveller is facing
	frontGridPosition.addDirection(direction);
	
	return g_environment->GetEntitiesAt(frontGridPosition, layer);
}

list<Entity*>* Traveller::GetAllFrontEntities(void) const
{
	list<Entity*>* r_entities = new list<Entity*>[3];

	r_entities[0] = GetFrontEntities(BOTTOM_LAYER);
	r_entities[1] = GetFrontEntities(MIDDLE_LAYER);
	r_entities[2] = GetFrontEntities(TOP_LAYER);

	return r_entities;
}