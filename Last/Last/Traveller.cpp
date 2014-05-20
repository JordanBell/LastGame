#include "Traveller.h"
#include "TravellerAnimation.h"
#include "Environment.h"
Traveller::Traveller(const Coordinates& _pos) : Entity(_pos, Coordinates(0, -TILE_SIZE/2), SSID_PLAYER, TRAVELLER_FRMT, NULL, new TravellerAnimation()), 
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
	if (m_format[GRID_INDEPENDENT]) m_moving = false;
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

	list<Entity*> frontEntities;
	
	// Check the bottom layer
	frontEntities = GetFrontEntities(false);
	for (Entity* ft : frontEntities) {
		if (!ft->CanMoveThrough()) return false;
	}

	// Check the top layer
	frontEntities = GetFrontEntities(true);
	for (Entity* ft : frontEntities) {
		if (!ft->CanMoveThrough()) return false;
	}

	return true;
}

list<Entity*>& Traveller::GetFrontEntities(bool top) const
{
	Coordinates& frontGridPosition = GetGridPosition();

	// Find the gridPosition in front of the direction the traveller is facing
	frontGridPosition.addDirection(direction);
	
	return g_environment->GetEntitiesAt(frontGridPosition, TOP_LAYER);
}