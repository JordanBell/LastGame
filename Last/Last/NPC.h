#pragma once
#include "traveller.h"
class NPC :
	public Traveller
{
public:
	NPC(const Coordinates& _pos) : Traveller(_pos) {}

protected:
	virtual void E_Update(const int delta);
	void E_OnInteract(void) { printf("Hello!\n"); }
};

