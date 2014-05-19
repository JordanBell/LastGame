#pragma once
#include "AnimationModule.h"

// An animation class specialised foor the Door Entity
class DoorAnimation : public AnimationModule
{
public:
	DoorAnimation(void) : AnimationModule(XY(5, 1), XY(32, 48), 5, 2) {}

	void Open(void);
	void Close(void);

protected:
	void Update(void);

private:
	void (*cycleFunction)(void); // The function that is called, to change the cycle of animation - Opening or Closing
};