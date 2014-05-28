#pragma once
#include "entity.h"
#include "Status.h"

/*
A UI component that is modelled after a (global) Status pointer.
*/
class UI_Status : public Entity
{
public:
	UI_Status(Status* status, const Coordinates& clipIndex);

protected:
	// Update this Entity based on the values held by the status model
	void E_Update(const int delta);

private:
	// The status this is modelled after
	Status* m_status;

	// Compute the clip struct from a given clipIndex of the status sprite sheet
	SDL_Rect ComputeClip(const Coordinates& clipIndex);

	// Compute the position from the clip index
	Coordinates ComputePosition(const Coordinates& clipIndex);
};

extern UI_Status* UI_Fatigue;
extern UI_Status* UI_Loneliness;
extern UI_Status* UI_Insanity;
extern UI_Status* UI_Fear;
