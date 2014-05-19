#include "Traveller.h"
#include "TravellerAnimation.h"
#include "Environment.h"

Traveller::Traveller(const XY& _pos) : Entity(_pos, XY(0, -TILE_SIZE/2), SSID_PLAYER, TRAVELLER_FRMT, NULL, new TravellerAnimation()), 
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
		misalignment += pixelsToMove;
	}

	// Check to see if the traveller should stop
	if (abs(misalignment) >= TILE_SIZE) // The traveller has reached the next tile
	{
		// Reset the movement variables
		m_moving = false;
		misalignment = 0;

		// Snap the traveller to a TILE_SIZE multiple.
		SnapPosition();
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
	// The traveller can move forward if none of the tiles in front of them are solid

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

list<TileEntity*>& Traveller::GetFrontTiles(bool top) const
{
	XY& frontGridPosition = GetGridPosition();

	// Find the gridPosition in front of the direction the traveller is facing
	frontGridPosition.addDirection(direction);
	
	return g_environment->GetTilesAt(frontGridPosition, top);
}