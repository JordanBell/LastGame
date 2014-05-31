#pragma once
#include "AnimationModule.h"

class DoorAnimation : public AnimationModule
{
public:
	DoorAnimation(void) 
		: AnimationModule(Dimensions(5, 1), Dimensions(32, 48), 5, 2), animateOpen(true) { on = false; }

	void Open(void);
	void Close(void);
	inline void StartDoor(bool opening) { if (opening) Open(); else Close(); }

protected:
	void Update(void);

private:
	bool animateOpen;
};