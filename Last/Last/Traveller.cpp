#include "Traveller.h"
#include "TravellerAnimation.h"
#include "Environment.h"
#include "SoundSource.h"

Traveller::Traveller(const Coordinates& _pos) 
	: EntityContainer(Dimensions(200, 200), 
					  _pos, 
					  Coordinates(0, -TILE_SIZE/2), 
					  SSID_PLAYER, 
					  TRAVELLER_FRMT, 
					  nullptr, 
					  new TravellerAnimation()),
	  direction(DOWN),
	  m_moving(false),
	  misalignment(0),
	  m_stillBuffer(0),
	  m_speed(TRAVELLER_SPEED),
	  m_soundSource(new SoundSource(this)),
	  m_talking(false)
{
	if (!m_format[TRAVELS]) 
		throw ModuleMisuseException("An entity cannot inherit from Traveller if its format does not allow travelling.");
	
	// Initialise animation as still
	a_module->OverrideCycle(1);
}

void Traveller::E_Update(const int delta)
{
	// Update whether or not this is talking.
	if (m_talking) m_talking = m_soundSource->IsActive();

	if (m_moving) // The traveller should keep moving in its currently assigned direction 
	{
		int pixelsToMove = m_speed * (1000/FRAME_RATE);
		
		// Move by this amount
		pos.addDirection(direction, pixelsToMove);

		// Increment the misalignment from the grid by this amount
		if (!m_format[GRID_INDEPENDENT]) misalignment += pixelsToMove;
	}
	else 
	{
		// Set the traveller as still, after a small buffer
		if (m_stillBuffer == 0) 
			a_module->OverrideCycle(1);
		else if (m_stillBuffer > 0)
			m_stillBuffer--;
	}

	// Check to see if the traveller should stop
	if (m_format[GRID_INDEPENDENT]) StopMoving(); // No need to check to see if at TILE_SIZE multiple if Grid Independent
	else
	{
		if (abs(misalignment) >= TILE_SIZE) // The traveller has reached the next tile
		{
			// Reset the movement variables
			StopMoving();

			misalignment = 0;

			// Snap the traveller to a TILE_SIZE multiple.
			SnapPosition();
		}
	}

	// Update the speech
	m_soundSource->Update(delta);
}

void Traveller::E_Render(void) 
{ 
	// Render this
	EntityContainer::E_Render(); 

	// Render the sound source's speech bubble above it.
	m_soundSource->Render(); 
}

void Traveller::Say(const string phrase, const bool priorityOverride, const int timeout) 
{ 
	if (ENABLE_SPEECH_BUBBLES)
	{
		// If not already talking, or if the phrase has priority override, speak.
		if (!m_talking || priorityOverride)
		{
			m_talking = true;
			if (timeout == -1) m_soundSource->Say(phrase);
			else			   m_soundSource->Say(phrase, timeout);
		}
	}
	else {} // No speech capabilities if speech bubbles disabled
}

void Traveller::Walk(const E_Direction& direction)
{
	// Only move if is not already in the motion of movement
	if (!m_moving)
	{		
		// Set the new direction
		TurnToFace(direction);

		// If the traveller can move to the next tile, start moving
		if (CanMoveForward()) StartMoving();
	}
}

void Traveller::StopMoving(void)
{
	m_moving = false;
	a_module->Stop();

	m_stillBuffer = 1;
}

void Traveller::StartMoving(void)
{
	m_moving = true;
	a_module->Start();
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